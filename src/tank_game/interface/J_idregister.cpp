//wriiten by JHN
#include "J_idregister.h"
#include "ui_idregister.h"
#include "J_mainwindow.h"
IDregister::IDregister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IDregister)
{
    ui->setupUi(this);
}

IDregister::~IDregister()
{
    delete ui;
}

void IDregister::on_pushButton_2_clicked()
{
    emit return_page1();
}

void IDregister::on_pushButton_clicked()
{
    new_ID=ui->NameEdit->text();//注册账号
    new_Password=ui->PasswordEdit->text();//注册密码
    emit regist(new_ID,new_Password);//注册信号
}
