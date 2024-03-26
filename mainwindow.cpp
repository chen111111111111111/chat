#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    all = nullptr;
    w=nullptr;

    msocket.connectToHost(QHostAddress("192.168.225.156"),60000);
    connect(&msocket,&QTcpSocket::connected,this,&MainWindow::connect_success);
}

MainWindow::~MainWindow()
{
    delete ui;
    msocket.close();
    if(all !=nullptr)
    delete all;
}

void MainWindow::connect_success()
{
    qDebug()<<"连接服务器成功";
    connect(&msocket,&QTcpSocket::readyRead,this,&MainWindow::recv_data);
}

void MainWindow::recv_data()
{
    QByteArray recv_buf = msocket.readAll();
    qDebug()<<1;
    qDebug()<<recv_buf;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(recv_buf,&err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug()<<"不是Json数据类型";
    }

    QJsonObject obj = doc.object();

    if(obj.contains("result"))
    {
        QString statu = obj.value("result").toString();
        QString name = obj.value("name").toString();
        if(statu == "ok")
        {
            qDebug()<<"登陆成功";
            all = new all_dialog(nullptr,msocket,ui->lineEdit->text());
            qDebug()<<ui->lineEdit->text();
            all->show();
            all->set(name);
            this->hide();
            all->move(1400,80);
            QJsonObject obj;
            obj.insert("switch","success");
            obj.insert("usr",ui->lineEdit->text());
            QJsonDocument doc(obj);
            msocket.write(doc.toJson());
            disconnect(&msocket,&QTcpSocket::readyRead,this,&MainWindow::recv_data);
        }
        else if(statu == "failed")
        {
            QMessageBox::warning(this,"登录提示","对不起，您的帐户或密码错误！\n请重新输入");
        }
    }
}

void MainWindow::send_register(QString name, QString usr, QString pwd)
{
    delete w;
    w=nullptr;
    QJsonObject obj;
    obj.insert("name",name);
    obj.insert("usr",usr);
    obj.insert("pwd",pwd);
    QJsonObject obj_all;
    obj_all.insert("register_info",obj);
    QJsonDocument doc(obj_all);
    msocket.write(doc.toJson());
}

void MainWindow::on_pushButton_2_clicked()
{
    QString usr = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();

    QJsonObject obj;
    obj.insert("usr",usr);
    obj.insert("pwd",pwd);

    QJsonObject all_obj;
    all_obj.insert("login",obj);
    QJsonDocument doc (all_obj);
    QByteArray send_buf = doc.toJson();
    msocket.write(send_buf);
}

void MainWindow::on_pushButton_clicked()
{
    if(w != nullptr)delete w;
    w = new Register_win(this);
    w->setWindowTitle("注册");
    connect(w,&Register_win::register_info,this,&MainWindow::send_register);
    w->setGeometry(800,300,400,800);
    w->show();
}
