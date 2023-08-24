#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include "errordialog.h"


RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::on_pushButton_clicked()
{
    if(ui->lineEdit->text() == ui->lineEdit_2->text()){
        qDebug() << "success";
        accept();
    }else{
        showErrorMassage("Not same passwords");
    }
}

void RegistrationDialog::showErrorMassage(QString errorText)
{
    ErrorDialog *errorDialog = new ErrorDialog(this, errorText);
    errorDialog->setWindowModality(Qt::ApplicationModal);
    errorDialog->exec();
}

QString RegistrationDialog::getValue() {
    return ui->lineEdit->text();
}

