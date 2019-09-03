//wriiten by JHN
#include "J_mainpage.h"
#include "ui_mainpage.h"
#include "map_maker/mapmaker.h"

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::on_Start_clicked()
{
    emit turn_page();
}

void MainPage::on_Exit_clicked()
{
    emit exit_page();
}

void MainPage::on_goto_mapmaker_clicked()
{
    Mapmaker *window = new Mapmaker(this);
    window->show();
}
