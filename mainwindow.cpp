#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"

#include <iostream>
#include <QGraphicsBlurEffect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *scrollWidget = new QWidget();

    ui->scrollArea->setWidget(scrollWidget);

    scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setAlignment(Qt::AlignTop);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/alexeygolubev/Documents/programming/PasswordManager/mydatabase.db");
    if (db.open()) {
        qDebug() << "Database opened!";
        query = QSqlQuery(db);
        query.exec("CREATE TABLE IF NOT EXISTS data (id INT PRIMARY KEY,name TEXT , login TEXT, password TEXT)");
        query.exec("SELECT MAX(id) FROM data");
        if (query.next()) {
            countOfFields = query.value(0).toInt();
            qDebug() << "Maximum id in the table: " << query.value(0).toInt();
        } else {
            qDebug() << "Error retrieving maximum id: " << query.lastError().text();
        }
        loadData();
    }else{
        qDebug() << "Database error!" << db.lastError().text();
    }
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
        countOfFields++;
        qDebug() << "Data inserted successfully!";
        PasswordField *field = new PasswordField(this, login, password, name, countOfFields);
        scrollLayout->insertWidget(0, field);
    }else{
        qDebug() << "Error inserting data: " << query.lastError().text();
    }

}

void MainWindow::authentification()
{

    //    AuthDialog *authDialog = new AuthDialog();
    //    authDialog->setWindowModality(Qt::ApplicationModal);
    //    if(authDialog->exec() == QDialog::Accepted){

    //    }
}

void MainWindow::loadData()
{
    query.prepare("SELECT * FROM data");
    if(query.exec()){
        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString login = query.value(2).toString();
            QString password = query.value(3).toString();
            PasswordField *field = new PasswordField(this, login, password, name, id);
            scrollLayout->insertWidget(0, field);
        }
    }
}

void MainWindow::on_pushButton_add_clicked()
{
    if(ui->lineEdit_password->text() != nullptr && ui->lineEdit_login->text() != nullptr /*&& ui->lineEdit_name->text != nullptr*/){
        this->addNewField(ui->lineEdit_login->text(), ui->lineEdit_password->text(), "Application");
        ui->lineEdit_login->clear();
        ui->lineEdit_password->clear();
    }else{
        qDebug() << "Free fields";
    }
}

