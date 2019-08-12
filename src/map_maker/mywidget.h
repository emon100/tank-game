#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "treewidget.h"

namespace Ui {
class mywidget;
}

class mywidget : public QWidget
{
    Q_OBJECT

public:
    explicit mywidget(QWidget *parent = nullptr);
    ~mywidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::mywidget *ui;
};

#endif // MYWIDGET_H
