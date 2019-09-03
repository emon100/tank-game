//wriiten by JHN
#include "J_players.h"
#include "ui_players.h"
#include "J_mainwindow.h"
Players::Players(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Players)
{
    ui->setupUi(this);
}

Players::~Players()
{
    delete ui;
}

void Players::on_pushButton_clicked()
{
    Player1=ui->Player_1->text();//玩家1名称
    Player2=ui->Player_2->text();//玩家2名称
    emit    Game_begin(Player1,Player2);//进入游戏
}

void Players::on_pushButton_2_clicked()
{
    emit turn_page3();
}
