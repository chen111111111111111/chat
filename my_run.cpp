#include "my_run.h"
#include <QDebug>
my_run::my_run(QSqlTableModel *model,QListWidget *list_w):model(model),list_w(list_w)
{

}

void my_run::run()
{
    model->setTable("message");
    model->select();
    qDebug()<<model->rowCount();
    for (int i = 0; i<model->rowCount(); i++) {
        qDebug()<<"123";
        QSqlRecord record = model->record(i);
        QVariant var0 = record.value(0);
        QVariant var1 = record.value(1);
        QVariant var2 = record.value(2);
        qDebug()<<"123";
        w = new chirld_dialog();
        qDebug()<<"123";
        w->setname(var0.toString());
        w->setusr(var1.toString());
        w->settext(var2.toString());
        QListWidgetItem *item =new QListWidgetItem;
        qDebug()<<"123";
        list_w->addItem(item);
        list_w->setItemWidget(item,w);
        qDebug()<<"123";
    }
}
