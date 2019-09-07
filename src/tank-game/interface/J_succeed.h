//wriiten by JHN
#ifndef SUCCEED_H
#define SUCCEED_H

#include <QWidget>

namespace Ui {
class Succeed;
}

class Succeed : public QWidget
{
    Q_OBJECT

public:
    explicit Succeed(QWidget *parent = nullptr);
    ~Succeed();
public slots:
    void show_id(QString id);
signals:
    void return_page1();
    void open_game(QString,QString);
private slots:

    void on_GameStart_clicked();

    void on_login_continue_clicked();

private:
    Ui::Succeed *ui;

    int users;
};

#endif // SUCCEED_H
