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
signals:
    void return_page2();
    void turn_page5();
private slots:
    void on_IDExit_clicked();

    void on_GameStart_clicked();

private:
    Ui::Succeed *ui;
};

#endif // SUCCEED_H
