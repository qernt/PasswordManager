#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = nullptr, MainWindow *mw = nullptr);
    ~AuthDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AuthDialog *ui;
    MainWindow *mainWindow;
};

#endif // AUTHDIALOG_H
