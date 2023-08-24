#include "passwordfield.h"
#include "ui_passwordfield.h"

PasswordField::PasswordField(QWidget *parent, QString login, QString password, QString applicationName, int ID, MainWindow *mw) :
    QWidget(parent),
    ui(new Ui::PasswordField)
{
    ui->setupUi(this);
    ui->label_application->setText(applicationName);
    ui->label_login->setText(login);
    ui->label_password->setText(password);

    id = ID;

    mainWindow = mw;

    qDebug() << id;

    connect(mainWindow, SIGNAL(changeFieldsId(int)), this, SLOT(changeId(int)));
}

PasswordField::~PasswordField()
{
    delete ui;
}

void PasswordField::on_pushButton_delete_clicked()
{
    this->deleteLater();
    mainWindow->deleteFieldfromDB(id);
}

void PasswordField::changeId(int deletedId)
{
    qDebug() << id;
    if(id > deletedId)
        id--;
}

