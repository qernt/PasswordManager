#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QtSql>


#include "passwordfield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void addNewField(QString login, QString password, QString name);
    void authentification();
    void registration();
    void loadData();
    void showErrorMassage(QString errorText);

private slots:
    void on_pushButton_add_clicked();

public:
    void deleteFieldfromDB(int id);
    QString makeHashFromString(QString inputString);
    QString readHash();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *scrollLayout;
    QSqlDatabase db;
    QSqlQuery query;
    int countOfFields = 1;
    QString password;

signals:
    void changeFieldsId(int deletedId);
    void successAuth();

};
#endif // MAINWINDOW_H
