#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
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
    void addField(QString login, QString password, QString name);
    void authentification();

private slots:
    void on_pushButton_add_clicked();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *scrollLayout;
};
#endif // MAINWINDOW_H
