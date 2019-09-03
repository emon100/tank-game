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
    void log(QString,QString);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IdlogPage *ui;
};

#endif // IDLOGPAGE_H
