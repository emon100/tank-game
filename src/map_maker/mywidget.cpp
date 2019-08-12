#include "mywidget.h"
#include "ui_mywidget.h"
#include "treewidget.h"
#include <QIcon>

mywidget::mywidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mywidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/Tank.ico"));
    setWindowTitle(tr("NEU王一蒙小组坦克大战"));
}

mywidget::~mywidget()
{
    delete ui;
}

void mywidget::on_pushButton_clicked()
{
    treewidget *mytree = new treewidget(this);
    mytree->setWindowFlag(Qt::Tool);
    mytree->show();
}
