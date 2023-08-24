#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"
#include "errordialog.h"
#include "registrationdialog.h"

#include <iostream>
#include <openssl/sha.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *scrollWidget = new QWidget();

    ui->scrollArea->setWidget(scrollWidget);

    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setAlignment(Qt::AlignTop);

    bool isRegistred = false;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/alexeygolubev/Documents/programming/PasswordManager/mydatabase.db");
    if (db.open()){
        qDebug() << "Database opened!";
        query = QSqlQuery(db);
        query.exec("CREATE TABLE IF NOT EXISTS data (id INT PRIMARY KEY,name TEXT , login TEXT, password TEXT)");
        query.prepare("SELECT * FROM data WHERE id = 0;");
        if (query.exec() && query.next()){
            isRegistred = true;
            query.exec("SELECT MAX(id) FROM data");
            if (query.next()) {
                countOfFields = query.value(0).toInt() + 1;
                qDebug() << "Maximum id in the table: " << query.value(0).toInt();
            }else{
                qDebug() << "Error retrieving maximum id: " << query.lastError().text();
            }
        }else
            isRegistred = false;
    }else{
        qDebug() << "Database error!" << db.lastError().text();
    }

    if(isRegistred)
        QTimer::singleShot(0, this, &MainWindow::authentification);
    else
        QTimer::singleShot(0, this, &MainWindow::registration);

    connect(this, &MainWindow::successAuth, &MainWindow::loadData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewField(QString login, QString password, QString name)
{
    query.prepare("INSERT INTO data (id, name, login, password) VALUES (:id, :name, :login, :password)");
    query.bindValue(":id", countOfFields);
    query.bindValue(":name", name);
    query.bindValue(":login", login);
    query.bindValue(":password", password);
    if(query.exec()){
        qDebug() << "Data inserted successfully!";
        PasswordField *field = new PasswordField(this, login, password, name, countOfFields, this);
        scrollLayout->insertWidget(0, field);
        countOfFields++;
    }else{
        qDebug() << "Error inserting data: " << query.lastError().text();
    }
}

void MainWindow::authentification()
{

    std::unique_ptr<AuthDialog> authDialog(new AuthDialog(nullptr, this));
    authDialog->setWindowModality(Qt::ApplicationModal);
    if(authDialog->exec() != QDialog::Accepted){
        QCoreApplication::exit();
    }else{
        emit successAuth();
    }
}

void MainWindow::loadData()
{
    query.prepare("SELECT * FROM data");
    if(query.exec()){
        while (query.next()) {
            int id = query.value(0).toInt();
            if(id != 0){
                QString name = query.value(1).toString();
                QString login = query.value(2).toString();
                QString password = query.value(3).toString();
                PasswordField *field = new PasswordField(this, login, password, name, id, this);
                scrollLayout->insertWidget(0, field);
            }
        }
    }else{
        qDebug() << "SQL error: " << query.lastError().text();
    }
}

void MainWindow::showErrorMassage(QString errorText)
{
    std::unique_ptr<ErrorDialog> errorDialog(new ErrorDialog(this, errorText));
    errorDialog->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    errorDialog->exec();
}

QString MainWindow::makeHashFromString(QString inputString)
{
    QByteArray byteArray = inputString.toUtf8(); // Преобразование строки в байтовый массив

    unsigned char hash[SHA256_DIGEST_LENGTH]; // Буфер для хеша
    SHA256((const unsigned char*)byteArray.data(), byteArray.size(), hash); // Выполнение хеширования

    // Преобразование хеша в строку HEX
    QString hashedString;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hashedString.append(QString("%1").arg(hash[i], 2, 16, QChar('0')));
    }

    return hashedString;
}

void MainWindow::on_pushButton_add_clicked()
{
    if(ui->lineEdit_password->text() != nullptr && ui->lineEdit_login->text() != nullptr /*&& ui->lineEdit_name->text != nullptr*/){
        this->addNewField(ui->lineEdit_login->text(), ui->lineEdit_password->text(), "Application");
        ui->lineEdit_login->clear();
        ui->lineEdit_password->clear();
    }else if(ui->lineEdit_password->text() == nullptr && ui->lineEdit_login->text() == nullptr){
        showErrorMassage("Password ang login fields are free");
    }
    else if(ui->lineEdit_password->text() == nullptr){
        showErrorMassage("Password field is free");
    }
    else if(ui->lineEdit_login->text() == nullptr){
        showErrorMassage("Login field is free");
    }
}


void MainWindow::deleteFieldfromDB(int id)
{
    query.prepare("DELETE FROM data WHERE id = :id");
    query.bindValue(":id", id);
    if (query.exec()) {
        query.prepare("UPDATE data SET id = id - 1 WHERE id > :id");
        query.bindValue(":id", id);
        if(query.exec()){
            countOfFields--;
            qDebug() << "deleted";
            emit changeFieldsId(id);
        }else
            qDebug() << "Update error:" << query.lastError().text();
    }else{
        qDebug() << "Delete error:" << query.lastError().text();
    }
}

QString MainWindow::readHash()
{
    query.prepare("SELECT * FROM data WHERE id = 0");
    if(query.exec()){
        if(query.next()){
            QString hash = query.value(3).toString();
            return hash;
        }else
            qDebug() << "SQL error: " << query.lastError().text();
    }else{
        qDebug() << "SQL error: " << query.lastError().text();
        return nullptr;
    }
}

void MainWindow::registration()
{
    std::unique_ptr<RegistrationDialog> registDialog(new RegistrationDialog());
    registDialog->setWindowModality(Qt::ApplicationModal);
    if(registDialog->exec() != QDialog::Accepted){
        QCoreApplication::exit();
    }else{
        query.prepare("INSERT INTO data (id, name, login, password) VALUES (0, 'hash', 'hash', :password)");
        password = registDialog->getValue();
        QString hashedPassword = makeHashFromString(password);
        query.bindValue(":password", hashedPassword);
        if(query.exec()){
            emit successAuth();
        }else{
            qDebug() << "SQL error: " << query.lastError().text();
        }
    }
}

