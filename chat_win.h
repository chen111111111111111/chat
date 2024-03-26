#ifndef CHAT_WIN_H
#define CHAT_WIN_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlRecord>
namespace Ui {
class chat_win;
}

class chat_win : public QWidget
{
    Q_OBJECT

public:
    explicit chat_win(QSqlDatabase &db, QWidget *parent = nullptr);
    ~chat_win();
    void set(QString usr,QString name,QString type,QString my_usr,QString my_name);
    void init();

signals:
    void send_message(QString text,QString usr,QString name,QString type);

public slots:
    void on_pushButton_clicked();
    void recv_show(QString name ,QString usr,QString text,QString time);
    void recv_group_show(QString name,QString usr,QString text,QString time,QString old_send_name,QString old_send_usr);

private:
    Ui::chat_win *ui;
    QString usr;
    QString name;
    QString type;
    QSqlTableModel *model;
    QSqlDatabase &db;
    QString my_usr;
    QString my_name;
};

#endif // CHAT_WIN_H
