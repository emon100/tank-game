#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class treewidget;
}

class treewidget : public QWidget
{
    Q_OBJECT

public:
    explicit treewidget(QWidget *parent = nullptr);
    ~treewidget();
    void init();
    void updateParentItem(QTreeWidgetItem *item);
private slots:

    void on_mainwindow_clicked();

private:
    Ui::treewidget *ui;
    static int fontsize;
};
#endif // TREEWIDGET_H
