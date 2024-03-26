#ifndef MESSAGE_RECORD_H
#define MESSAGE_RECORD_H

#include <QWidget>

namespace Ui {
class message_record;
}

class message_record : public QWidget
{
    Q_OBJECT

public:
    explicit message_record(QWidget *parent = nullptr);
    ~message_record();
    void set(QString time,QString name,QString text);

private:
    Ui::message_record *ui;
};

#endif // MESSAGE_RECORD_H
