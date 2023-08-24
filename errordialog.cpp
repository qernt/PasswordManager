#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent,  QString errorText) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);

    ui->label->setText(errorText);
    ui->label->setAlignment(Qt::AlignCenter);

    this->setFixedSize(300,300);
    this->setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->pushButton, &QPushButton::clicked, this, &QDialog::accept);
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}
