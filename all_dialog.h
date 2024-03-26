#ifndef ALL_DIALOG_H
#define ALL_DIALOG_H

#include <QMainWindow>
#include <QTcpSocket>
//数据库头文件
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

//数据库文件显示
#include <QSqlTableModel>

#include <QThreadPool>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "chirld_dialog.h"
#include <QSet>
namespace Ui {
class all_dialog;
}

class all_dialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit all_dialog(QWidget *parent = nullptr);
    all_dialog(QWidget *parent,QTcpSocket &msocket,QString usr);
    ~all_dialog();
    void getsocket(QTcpSocket &msoket);
    void set(QString name);
signals:
    void recv_message(QString name,QString usr,QString text,QString time);
    void recv_message_group(QString name,QString usr,QString text,QString time,QString old_send_name,QString old_send_usr);
public slots:
    void recv_data();
    void send_buf(QString text,QString usr,QString name,QString type);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::all_dialog *ui;
    QTcpSocket& msocket;
    QString usr;
    QString name;
    QSqlDatabase db;
    QSqlTableModel *model;
    chirld_dialog *w;
    QSet<chirld_dialog *> tree;
};

#endif // ALL_DIALOG_H
