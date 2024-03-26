#ifndef REGISTER_WIN_H
#define REGISTER_WIN_H

#include <QMainWindow>

namespace Ui {
class Register_win;
}

class Register_win : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register_win(QWidget *parent = nullptr);
    ~Register_win();
signals:
    void register_info(QString name,QString usr,QString pwd);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Register_win *ui;
};

#endif // REGISTER_WIN_H
