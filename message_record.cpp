#include "message_record.h"
#include "ui_message_record.h"

message_record::message_record(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::message_record)
{
    ui->setupUi(this);
}

message_record::~message_record()
{
    delete ui;
}

void message_record::set(QString time, QString name, QString text)
{
    ui->label->setText(name);
    ui->label_2->setText(text);
    ui->label_3->setText(time);
}
