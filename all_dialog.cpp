#include "all_dialog.h"
#include "ui_all_dialog.h"
#include<QDebug>
#include <QMessageBox>
all_dialog::all_dialog(QWidget *parent,QTcpSocket& msocket,QString usr) :
    QMainWindow(parent),
    ui(new Ui::all_dialog),
    msocket(msocket),
    usr(usr)
{
    ui->setupUi(this);
    setWindowTitle("双Q天下无敌！");
    connect(&msocket,&QTcpSocket::readyRead,this,&all_dialog::recv_data);
    QByteArray recv_buf = msocket.readAll();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("usr.db");
    db.open();
    QString sql = QString("create table message(send_name text,send_usr text,recv_usr text,text text,time text,type text,old_name text,old_usr text);");
    db.exec(sql);
    if(db.isOpen())
    {
        qDebug()<<"数据库打开";
    }
    model = new QSqlTableModel(this,db);
    model->setTable("message");

//    //开始加载聊天对话框
//
//
//    model->setFilter(QString("recvusr = '%1'").arg(usr));
//    model->select();
//    qDebug()<<model->rowCount()<< "  "<<usr;
//    //m_run = new my_run(model,ui->listWidget);
//    //pool->start(m_run,0);
//    for (int i = 0; i<model->rowCount(); i++)
//    {
//        QSqlRecord record = model->record(i);
//        QVariant var0 = record.value(0);
//        QVariant var1 = record.value(1);
//        QVariant var3 = record.value(3);
//        QVariant var4 = record.value(4);
//        QVariant var5 = record.value(5);
//        w = new chirld_dialog(db,this);
//        w->setname(var0.toString());
//        w->setusr(var1.toString());
//        w->settime(var4.toString());
//        w->settext(var3.toString());
//        w->settype(var5.toString());
//        QListWidgetItem *item =new QListWidgetItem;
//        item->setSizeHint(w->size());
//        ui->listWidget->addItem(item);
//        ui->listWidget->setItemWidget(item,w);

//    }
}

all_dialog::~all_dialog()
{
    delete ui;
}


void all_dialog::set(QString name)
{
    this->name = name;
    ui->label->setText(name);
}

void all_dialog::recv_data()
{
    qDebug()<<2;
    QByteArray recv_buf = msocket.readAll();
    qDebug()<<recv_buf;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(recv_buf,&err);
    if(err.error != QJsonParseError::NoError)
    {
       qDebug()<<"不是Json数据类型";
       return ;
    }
    QJsonObject all_obj= doc.object();

    if(all_obj.contains("relations"))
    {
        QJsonArray obj_arry = all_obj.value("relations").toArray();
        for (int i = 0;i<obj_arry.size();i++)
        {
            QJsonObject obj = obj_arry[i].toObject();
            QString name = obj.value("name").toString();
            QString usr = obj.value("usr").toString();
            QString type = obj.value("type").toString();

            QListWidgetItem *item = new QListWidgetItem;
            chirld_dialog *w = new chirld_dialog(db);
            item->setSizeHint(w->size());
            w->setname(name);
            w->setusr(usr);
            w->settype(type);
            w->settime("");
            w->settext("暂无消息");
            w->setmyusr(this->usr);
            w->setmyname(this->name);
            qDebug()<<name<<" "<<usr<<" 关系："<<type;
            if(type =="friend")connect(this,&all_dialog::recv_message,w,&chirld_dialog::recv_message_mid);
            else if(type == "group")connect(this,&all_dialog::recv_message_group,w,&chirld_dialog::recv_message_group_mid);
            connect(w,&chirld_dialog::send_all,this,&all_dialog::send_buf);
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item,w);
        }
        QJsonObject obj2;
        obj2.insert("ready_recv",this->usr);
        obj2.insert("name",this->name);
        QJsonDocument doc1(obj2);
        msocket.write(doc1.toJson());
    }
    else if(all_obj.contains("out_line_text"))                  //接受离线消息
    {
        QJsonArray arry = all_obj.value("out_line_text").toArray();

        int n = arry.size();
        qDebug()<<"开始接收离线消息:"<<n;
        for (int i = 0; i<n ; i++) {
            QJsonObject obj = arry.at(i).toObject();
            QString name = obj.value("send_name").toString();
            QString usr = obj.value("send_usr").toString();
            QString text = obj.value("text").toString();
            QString time = obj.value("time").toString();
            QString type = obj.value("type").toString();
            model->setFilter("");
            model->select();
            QSqlRecord record = model->record(0);
            record.setValue("send_name",name);
            record.setValue("send_usr",usr);
            record.setValue("text",text);
            record.setValue("time",time);
            record.setValue("recv_name",this->name);
            record.setValue("recv_usr",this->usr);
            record.setValue("type",type);
            if(type =="group")
            {
                QString old_send_name = obj.value("old_send_name").toString();
                QString old_send_usr = obj.value("old_send_usr").toString();
                record.setValue("old_send_name",old_send_name);
                record.setValue("old_send_usr",old_send_usr);
                emit recv_message_group(name,usr,text,time,old_send_name,old_send_usr);
            }
            model->insertRecord(0,record);
            if(type == "friend") emit recv_message(name,usr,text,time);
        }
    }
    else if(all_obj.contains("send_message"))               //在线信息
    {
        QJsonObject obj = all_obj.value("send_message").toObject();
        QString send_name = obj.value("send_name").toString();
        QString send_usr = obj.value("send_usr").toString();
        QString time = obj.value("time").toString();
        QString type = obj.value("type").toString();
        QString text = obj.value("text").toString();
        model->select();
        QSqlRecord record = model->record(0);
        record.setValue("send_name",send_name);
        record.setValue("send_usr",send_usr);
        record.setValue("text",text);
        record.setValue("time",time);
        record.setValue("recv_name",this->name);
        record.setValue("recv_usr",this->usr);
        record.setValue("type",type);
        record.setValue("old_send_name","");
        record.setValue("old_send_usr","");
        if(type =="group")
        {
            QString old_send_name = obj.value("old_send_name").toString();
            QString old_send_usr = obj.value("old_send_usr").toString();
            record.setValue("old_send_name",old_send_name);
            record.setValue("old_send_usr",old_send_usr);
            emit recv_message_group(send_name,send_usr,text,time,old_send_name,old_send_usr);
            qDebug()<<"在线消息解析群："<<send_name<<" "<<send_usr<<" "<<time<<" ";

        }

        model->insertRecord(0,record);
        if(type == "friend")
        {
            qDebug()<<"在线消息解析好友："<<send_name<<" "<<send_usr<<" "<<time;
            emit recv_message(send_name,send_usr,text,time);
        }
    }
    else if(all_obj.contains("add_failed"))
    {
        QString recv_usr = all_obj.value("add_failed").toString();
        QMessageBox::warning(this,"添加提示",QString("对不起，您添加用户'%1'不存在").arg(recv_usr));
    }
    else if(all_obj.contains("register_result"))
    {
        QString ret = all_obj.value("register_result").toString();
        if(ret =="no")
        {
            QMessageBox::warning(this,"注册提示","注册失败，该用账号存在！");
        }
        else {
            QMessageBox::warning(this,"注册提示","注册成功！！！");
        }
    }
}

void all_dialog::send_buf(QString text, QString usr,QString name,QString type)
{
    QJsonObject obj;
    obj.insert("text",text);
    obj.insert("recv_usr",usr);
    obj.insert("recv_name",name);
    obj.insert("send_usr",this->usr);
    obj.insert("send_name",this->name);
    QJsonObject all_obj;
    if(type == "friend")all_obj.insert("sendMessageToFriend",obj);
    else if(type == "group")all_obj.insert("sendMessageToGroup",obj);
    QJsonDocument doc(all_obj);
    qDebug()<<"111"<<doc.toJson()<<" "<<type;
    msocket.write(doc.toJson());
}

void all_dialog::on_pushButton_clicked()
{
    if(ui->lineEdit ->text() == "")
    {
        QMessageBox::warning(this,"添加提示","请输入用户账号添加");
        return;
    }
    else
    {
        QJsonObject obj;
        obj.insert("send_name",name);
        obj.insert("send_usr",usr);
        obj.insert("recv_usr",ui->lineEdit->text());
        qDebug()<<ui->lineEdit->text();
        ui->lineEdit->clear();
        qDebug()<<ui->lineEdit->text();
        QJsonObject all_obj;
        all_obj.insert("add_friend",obj);
        QJsonDocument doc(all_obj);
        msocket.write(doc.toJson());
    }
}

void all_dialog::on_pushButton_3_clicked()
{
    if(ui->lineEdit_2->text() == ""||ui->lineEdit_3->text()=="")
    {
        QMessageBox::warning(this,"建群提示","请输入完整的群名和群号！");
        return ;
    }
    QString group_name = ui->lineEdit_2->text();
    QString group_id = ui->lineEdit_3->text();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    QJsonObject obj;
    obj.insert("group_name",group_name);
    obj.insert("group_id",group_id);
    obj.insert("send_name",this->name);
    obj.insert("send_usr",this->usr);
    QJsonObject all_obj;
    all_obj.insert("create_group",obj);
    QJsonDocument doc(all_obj);
    msocket.write(doc.toJson());
}
