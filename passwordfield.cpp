#include "passwordfield.h"
#include "ui_passwordfield.h"

PasswordField::PasswordField(QWidget *parent, const QString &login, const QString &password, const QString &applicationName, const int &ID) :
    QWidget(parent),
    ui(new Ui::PasswordField)
{
    ui->setupUi(this);
    ui->label_application->setText(applicationName);
    ui->label_login->setText(login);
    ui->label_password->setText(password);

    id = ID;
}

PasswordField::~PasswordField()
{
    delete ui;
}

void PasswordField::on_pushButton_delete_clicked()
{
    this->deleteLater();   
}

