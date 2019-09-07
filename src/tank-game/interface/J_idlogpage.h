//wriiten by JHN
#ifndef IDLOGPAGE_H
#define IDLOGPAGE_H

#include <QWidget>

namespace Ui {
class IdlogPage;
}

class IdlogPage : public QWidget
{
    Q_OBJECT

public:
    explicit IdlogPage(QWidget *parent = nullptr);
    ~IdlogPage();
signals:
    void return_page1();
    void log_succeed();
    void success_ID(QString);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IdlogPage *ui;
        QString user1;//之前登录的用户名字
};

#endif // IDLOGPAGE_H
