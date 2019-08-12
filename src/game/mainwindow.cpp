#include "mainwindow.h"
#include "LoginDig.h"
#include "ui_mainwindow.h"
#include <QGridLayout>

const double PI=3.1415;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countBtn_clicked()//信号
{
    bool ok;
    QString tempstr;
    QString valuestr=ui->radiusLineEdit->text();
    int valueInt=valuestr.toInt(&ok);
    double area = valueInt*valueInt*PI;
    ui->areaLabel_2->setText(tempstr.setNum(area));
}

void MainWindow::on_loginButton_clicked()
{
    LoginDig *dlg = new LoginDig(this);
    dlg->show();
    if(dlg->exec() == LoginDig::Rejected)
        return;
}
