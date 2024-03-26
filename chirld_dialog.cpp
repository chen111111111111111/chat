#include "chirld_dialog.h"
#include "ui_chirld_dialog.h"
#include <QDebug>
#include "all_dialog.h"
#include "message_record.h"
chirld_dialog::chirld_dialog(QSqlDatabase &db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chirld_dialog),
    db(db)
{
    ui->setupUi(this);
    w =nullptr;
}

chirld_dialog::~chirld_dialog()
{
    delete ui;
}

bool chirld_dialog::event(QEvent *e)
{
    if(e->type() == QEvent::MouseButtonDblClick)
    {
        qDebug()<<"双击了";
        if(w != nullptr)
        {
            w->close();
            delete w;
        }
        w = new chat_win(db);
        w->set(usr,ui->label->text(),type,my_usr,my_name);
        w->setGeometry(600,250,600,600);
        w->show();
        w->setWindowTitle(ui->label->text());
        w->init();
        connect(w,&chat_win::send_message,this,&chirld_dialog::send_mid);
        if(type =="friend")connect(this,&chirld_dialog::recv_show_mid,w,&chat_win::recv_show);
        else if(type =="group")connect(this,&chirld_dialog::recv_group_show_mid,w,&chat_win::recv_group_show);

    }
    return QWidget::event(e);
}

void chirld_dialog::setname(QString name)
{
    ui->label->setText(name);
}

void chirld_dialog::settime(QString t)
{
    ui->label_2->setText(t);
}

void chirld_dialog::setusr(QString usr)
{
    this->usr = usr;
}

void chirld_dialog::settext(QString text)
{
    ui->label_3->setText(text);
}

void chirld_dialog::settype(QString type)
{
    this->type = type;
}

void chirld_dialog::setmyusr(QString my_usr)
{
    this ->my_usr = my_usr;
}

void chirld_dialog::setmyname(QString my_name)
{
    this->my_name = my_name;
}


void chirld_dialog::chirld_end()
{
    w =nullptr;
}

void chirld_dialog::send_mid(QString text, QString usr,QString name,QString type)
{
    qDebug()<<"中转"<<text<<" "<<usr<<" "<<name<<" "<<type;
    emit send_all(text,usr,name,type);
}

void chirld_dialog::recv_message_mid(QString name, QString usr, QString text, QString time)
{
    qDebug()<<usr<< " "<<this->usr;
    if(usr == this->usr)
    {
        ui->label->setText(name);
        ui->label_2->setText(time);
        ui->label_3->setText(text);
        emit recv_show_mid(name,usr,text,time);
        qDebug()<<"接受好友信息信号";
    }
}

void chirld_dialog::recv_message_group_mid(QString name, QString usr, QString text, QString time, QString old_send_name, QString old_send_usr)
{
    qDebug()<<usr<< " "<<this->usr;
    if(usr == this->usr)
    {
        ui->label->setText(name);
        ui->label_2->setText(time);
        ui->label_3->setText(text);
        emit recv_group_show_mid(name,usr,text,time,old_send_name,old_send_usr);
        qDebug()<<"接受群信息信号";
    }
}

