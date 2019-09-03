//wriiten by JHN
#include "J_succeed.h"
#include "ui_succeed.h"
#include "J_mainwindow.h"
Succeed::Succeed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Succeed)
{
    ui->setupUi(this);
    ui->CurrentID->setText(ID);/////当前登陆用户
}

Succeed::~Succeed()
{
    delete ui;
}


void Succeed::on_IDExit_clicked()
{
    emit return_page2();
    ID=" ";
}

void Succeed::on_GameStart_clicked()
{
    emit turn_page5();
}
