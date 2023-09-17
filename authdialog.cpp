#include "authdialog.h"
#include "errordialog.h"
#include "ui_authdialog.h"

#include <QCloseEvent>

AuthDialog::AuthDialog(QWidget *parent,  MainWindow *mw) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    mainWindow = mw;
}

AuthDialog::~AuthDialog()
{
    delete ui;
}


void AuthDialog::on_pushButton_clicked()
{
    if(mainWindow->makeHashFromString(ui->lineEdit->text()) == mainWindow->readHash()){
        mainWindow->setLoginPassword(ui->lineEdit->text());
        accept();
    }else{
        ErrorDialog *errorDialog = new ErrorDialog(this, "Incorrect password");
        errorDialog->setWindowModality(Qt::ApplicationModal);
        errorDialog->exec();
        ui->lineEdit->clear();
        qDebug() << "False password";
    }
}

