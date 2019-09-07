//wriiten by JHN
#include "J_loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}
////////转至主页面////////
void LoginPage::on_pushButton_4_clicked()
{
    emit return_page();
}

void LoginPage::on_pushButton_clicked()
{
    emit id_login();
}

void LoginPage::on_pushButton_2_clicked()
{
    emit turn_idregister();
}

void LoginPage::on_pushButton_3_clicked()
{
    emit turn_page6();
}
