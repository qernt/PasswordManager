#ifndef PASSWORDFIELD_H
#define PASSWORDFIELD_H

#include <QWidget>

namespace Ui {
class PasswordField;
}

class PasswordField : public QWidget
{
    Q_OBJECT

public:
    explicit PasswordField(QWidget *parent = nullptr, const QString &login = "", const QString &password = "", const QString &applicationName = "");
    ~PasswordField();

private slots:
    void on_pushButton_delete_clicked();

private:
    Ui::PasswordField *ui;
};

#endif // PASSWORDFIELD_H
