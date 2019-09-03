//wriiten by JHN
#include "J_idlogpage.h"
#include "ui_idlogpage.h"
#include "J_mainwindow.h"
IdlogPage::IdlogPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdlogPage)
{
    ui->setupUi(this);
}

IdlogPage::~IdlogPage()
{
    delete ui;
}

void IdlogPage::on_pushButton_2_clicked()
{
    emit return_page1();
}

void IdlogPage::on_pushButton_clicked()
{
    ID=ui->NameEdit->text();//登陆账号
    Password=ui->PasswordEdit->text();//登陆密码
    emit log(ID,Password);//登陆信号
}
