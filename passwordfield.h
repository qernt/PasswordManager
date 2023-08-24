#ifndef PASSWORDFIELD_H
#define PASSWORDFIELD_H

#include <QWidget>
#include <mainwindow.h>

class MainWindow;

namespace Ui {
class PasswordField;
}

class PasswordField : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordField(QWidget *parent = nullptr, QString login = "", QString password = "", QString applicationName = "", int ID = 0, MainWindow *mw = nullptr);
    ~PasswordField();

private slots:
    void on_pushButton_delete_clicked();
    void changeId(int deletedId);

public:
    int id;

private:
    Ui::PasswordField *ui;
    MainWindow *mainWindow;
};

#endif // PASSWORDFIELD_H
