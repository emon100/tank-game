//wriiten by JHN
#include "J_currentplayer.h"
#include "ui_currentplayer.h"
#include "J_mainwindow.h"
#include <QMessageBox>
CurrentPlayer::CurrentPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentPlayer)
{
    ui->setupUi(this);
}

CurrentPlayer::~CurrentPlayer()
{
    delete ui;
}

void CurrentPlayer::on_pushButton_clicked()
{
    if(ui->current1->text()==ui->current2->text()){
    ui->current1->clear();
    ui->current2->clear();
        QMessageBox fail(QMessageBox::Warning,"登录失败","玩家名不可重复！",QMessageBox::Ok);
        fail.exec();
        return;
    }
    emit    Game_begin("guest"+ui->current1->text(),"guest"+ui->current2->text());
    ui->current1->clear();
    ui->current2->clear();
}

void CurrentPlayer::on_pushButton_2_clicked()
{
    emit turn_page1();
}
