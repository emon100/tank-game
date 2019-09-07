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

    emit    Game_begin(ui->current1->text(),ui->current2->text());
}

void CurrentPlayer::on_pushButton_2_clicked()
{
    emit turn_page1();
}
