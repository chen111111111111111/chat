#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//自定义对象头文件
#include "all_dialog.h"
#include "my_run.h"
#include "register_win.h"
//数据库头文件
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

//数据库文件显示
#include <QSqlTableModel>

//服务器套接字头文件
#include <QTcpServer>
#include <QTcpSocket>

//Json数据头文件
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>

//容器头文件
#include <QSet>

//提示弹窗头文件
#include <QMessageBox>

//线程池头文件
#include <QThreadPool>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void connect_success();
    void recv_data();
    void send_register(QString name,QString usr,QString pwd);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket msocket;
    all_dialog *all;
    Register_win *w;
};

#endif // MAINWINDOW_H
