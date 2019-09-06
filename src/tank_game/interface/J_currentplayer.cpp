//wriiten by JHN
#include "J_currentplayer.h"
#include "ui_currentplayer.h"
#include "J_mainwindow.h"
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
    Player1=ui->current1->text();//玩家1名称
    Player2=ui->current2->text();//玩家2名称
    emit    Game_begin(Player1,Player2);//进入游戏
}

void CurrentPlayer::on_pushButton_2_clicked()
{
    emit turn_page1();
}
