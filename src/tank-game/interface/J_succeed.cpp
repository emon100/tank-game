//wriiten by JHN
#include "J_succeed.h"
#include "ui_succeed.h"
#include "J_mainwindow.h"
Succeed::Succeed(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Succeed),
    users(0)
{
    ui->setupUi(this);
    ui->GameStart->hide();
}

Succeed::~Succeed()
{
    delete ui;
}



void Succeed::show_id(QString id){
    users++;
    if(users==1){
        ui->user1->setText(id);
        ui->user2->setText("未登录");
    }else{
        ui->GameStart->show();
        ui->login_continue->hide();
        ui->user2->setText(id);
    }

}

void Succeed::on_GameStart_clicked()
{
    emit open_game(ui->user1->text(),ui->user2->text());
}

void Succeed::on_login_continue_clicked()
{
    emit return_page1();
}
