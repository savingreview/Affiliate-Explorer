#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QtNetwork>
#include <QDebug>

#include "global.h"
#include "pugixml.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    void binding();

private slots:
    void fuckoff();
    void fuckoff2();
    void handleNetworkData(QNetworkReply *networkReply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager networkmanager;
};

#endif // MAINWINDOW_H
