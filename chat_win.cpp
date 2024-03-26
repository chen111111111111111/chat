#include "chat_win.h"
#include "ui_chat_win.h"
#include <QDebug>
#include "message_record.h"
#include <QTime>
#include <QDate>
chat_win::chat_win(QSqlDatabase &db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat_win),
    db(db)
{
    ui->setupUi(this);
    model = new QSqlTableModel(this,db);
}

chat_win::~chat_win()
{
    delete ui;
}

void chat_win::set(QString usr,QString name,QString type,QString my_usr,QString my_name)
{
    this->usr = usr;
    this->type = type;
    this->name = name;
    this->my_usr = my_usr;
    this->my_name = my_name;
}

void chat_win::init()
{
    model->setTable("message");
    model->setFilter(QString("(send_usr = '%1'and recv_usr = '%2') or(send_usr = '%2' and recv_usr = '%1') ").arg(usr).arg(my_usr));
    model->select();
    int n = model->rowCount();
    qDebug()<<usr<<":"<<n;
    for (int i = 0;i<n;i++) {

        QSqlRecord record =  model->record(i);
        QString send_name;
        if(type == "friend")send_name= record.value("send_name").toString();
        if(type == "group")send_name= record.value("old_send_name").toString();
        QString time = record.value("time").toString();
        QString text = record.value("text").toString();
        message_record *w = new message_record;
        w->set(time,send_name,text);
        if(send_name == my_name)w->setStyleSheet("background-color:rgb(0,255,0);");
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(w->size());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,w);
    }
}

void chat_win::on_pushButton_clicked()
{


    QString text = ui->textEdit_2->toPlainText();
    qDebug()<<"1"<<text<<" "<<usr<<" "<<windowTitle()<<" "<<type;
    emit send_message(text,usr,windowTitle(),type);
    ui->textEdit_2->clear();
    message_record *w = new message_record;
    QString time = QDate::currentDate().toString("yyyy-MM-dd");
    time.append( QTime::currentTime().toString(" hh-mm-ss"));
    w->set(time,my_name,text);
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(w->size());
    w->setStyleSheet("background-color:rgb(0,255,0);");

    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,w);
    w->show();
    QSqlRecord record =  model->record(0);
    record.setValue("send_name",my_name);
    record.setValue("send_usr",my_usr);
    record.setValue("recv_usr",this->usr);
    record.setValue("recv_name",this->name);
    record.setValue("time",time);
    record.setValue("text",text);
    record.setValue("old_send_name",my_name);
    record.setValue("old_send_usr",my_name);
    record.setValue("type",type);
    model->insertRecord(0,record);
}

void chat_win::recv_show(QString name, QString usr, QString text, QString time)
{
    QListWidgetItem *item = new QListWidgetItem;
    message_record *w = new message_record(this);
    item->setSizeHint(w->size());
    w->set(time,name,text);
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,w);
    w->show();
}

void chat_win::recv_group_show(QString name, QString usr, QString text, QString time, QString old_send_name, QString old_send_usr)
{
    QListWidgetItem *item = new QListWidgetItem;
    message_record *w = new message_record(this);
    item->setSizeHint(w->size());
    w->set(time,old_send_name,text);
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,w);
    w->show();
}
