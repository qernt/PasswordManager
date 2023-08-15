#include "authdialog.h"
#include "ui_authdialog.h"

#include <QCloseEvent>

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &QDialog::accept);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

