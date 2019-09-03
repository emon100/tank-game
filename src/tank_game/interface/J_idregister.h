//wriiten by JHN
#ifndef IDREGISTER_H
#define IDREGISTER_H

#include <QWidget>

namespace Ui {
class IDregister;
}

class IDregister : public QWidget
{
    Q_OBJECT

public:
    explicit IDregister(QWidget *parent = nullptr);
    ~IDregister();
signals:
    void return_page1();
    void regist(QString,QString);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IDregister *ui;
};

#endif // IDREGISTER_H
