#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authdialog.h"

#include <iostream>
#include <QGraphicsBlurEffect>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addField(QString login, QString password, QString name)
{
    std::cout << "succes" << std::endl;
    PasswordField *field = new PasswordField(this, login, password, name);
    scrollLayout->insertWidget(0, field);
}

void MainWindow::authentification()
{

//    AuthDialog *authDialog = new AuthDialog();
//    authDialog->setWindowModality(Qt::ApplicationModal);
//    if(authDialog->exec() == QDialog::Accepted){
//        QWidget *scrollWidget = new QWidget();

//        ui->scrollArea->setWidget(scrollWidget);

//        scrollLayout = new QVBoxLayout(scrollWidget);
//        scrollLayout->setAlignment(Qt::AlignTop);
//    }
}

void MainWindow::on_pushButton_add_clicked()
{
//    if(ui->lineEdit_password->text() != nullptr && ui->lineEdit_login->text() != nullptr && ui->lineEdit_name->text != nullptr){
//        this->addField(ui->lineEdit_login->text(), ui->lineEdit_password->text());
//        ui->lineEdit_login->clear();
//        ui->lineEdit_password->clear();
//    }else{
//        std::cout << "free fields" << std::endl;
//    }
    this->addField("login", "password", "application");
    ui->lineEdit_login->clear();
    ui->lineEdit_password->clear();
}

