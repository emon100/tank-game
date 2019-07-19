#include "logindig.h"
#include "ui_logindig.h"

LoginDig::LoginDig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDig)
{
    ui->setupUi(this);
}

LoginDig::~LoginDig()
{
    delete ui;
}
