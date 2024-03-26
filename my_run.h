#ifndef MY_RUN_H
#define MY_RUN_H

#include <QSqlTableModel>
#include <QRunnable>
#include "chirld_dialog.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QSqlRecord>
#include <QVariant>
class my_run : public QRunnable
{
public:
    my_run(QSqlTableModel *model,QListWidget *list_w);
    void run();
private:
    QSqlTableModel *model;
    QListWidget *list_w;
    chirld_dialog *w;
};

#endif // MY_RUN_H
