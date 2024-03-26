#ifndef CHIRLD_DIALOG_H
#define CHIRLD_DIALOG_H

#include <QWidget>
#include "chat_win.h"
#include <QSqlTableModel>
namespace Ui {
class chirld_dialog;
}

class chirld_dialog : public QWidget
{
    Q_OBJECT

public:
    explicit chirld_dialog(QSqlDatabase &db,QWidget *parent = nullptr);
    ~chirld_dialog();
    bool event(QEvent *e);
    void setname(QString title);
    void settime(QString t);
    void setusr(QString usr);
    void settext(QString text);
    void settype(QString type);
    void setmyusr(QString my_usr);
    void setmyname(QString my_name);
signals:
    void send_all(QString text,QString usr,QString name,QString type);
    void recv_show_mid(QString name,QString usr,QString text,QString time);
    void recv_group_show_mid(QString name,QString usr,QString text,QString time,QString old_send_name,QString old_send_usr);
public slots:
    void chirld_end();
    void send_mid(QString text,QString usr,QString name,QString type);
    void recv_message_mid(QString name,QString usr,QString text,QString time);
    void recv_message_group_mid(QString name,QString usr,QString text,QString time,QString old_send_name,QString old_send_usr);
private:
    Ui::chirld_dialog *ui;
    QString usr;
    QString type;
    chat_win *w;
    QSqlDatabase &db;
    QString my_usr;
    QString my_name;
};

#endif // CHIRLD_DIALOG_H
