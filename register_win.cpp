#include "register_win.h"
#include "ui_register_win.h"
#include <QMessageBox>
Register_win::Register_win(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register_win)
{
    ui->setupUi(this);
}

Register_win::~Register_win()
{
    delete ui;
}

void Register_win::on_pushButton_clicked()
{
    QString name = ui->lineEdit->text();
    QString usr = ui->lineEdit_2->text();
    QString pwd = ui->lineEdit_3->text();
    QString pwd2 =ui->lineEdit_4->text();
    if(pwd != pwd2)
    {
        QMessageBox::warning(this,"创建提示","两次输入的密码不一致！");
        return;
    }
    emit register_info(name,usr,pwd);
}
