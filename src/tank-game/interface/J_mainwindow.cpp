//wriiten by JHN
#include "J_mainwindow.h"
#include "ui_mainwindow.h"
#include "game/game_widget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainPage *main= new MainPage();
    LoginPage *login= new LoginPage();
    IdlogPage *idlogin= new IdlogPage();
    Succeed *ls= new Succeed();
    IDregister *regis= new IDregister();
    CurrentPlayer *current=new CurrentPlayer();
    ui->stackedWidget->addWidget(main);//主页。。。。。。0
    ui->stackedWidget->addWidget(login);//登录页.。。。。1
    ui->stackedWidget->addWidget(idlogin);//账号登陆.。。2
    ui->stackedWidget->addWidget(ls);//登陆成功.。。。。。3
    ui->stackedWidget->addWidget(regis);//账号注册.。。。4
    ui->stackedWidget->addWidget(current);//临时登陆玩家姓名。。。5
    ui->stackedWidget->setCurrentIndex(0);
    connect(main,&MainPage::turn_page,this,&MainWindow::turn);
    connect(main,&MainPage::exit_page,this,&MainWindow::exit);
    connect(login,&LoginPage::return_page,this,&MainWindow::turnToMain);
    connect(login,&LoginPage::id_login,this,&MainWindow::turn2);
    connect(idlogin,&IdlogPage::return_page1,this,&MainWindow::turn1);
    connect(login,&LoginPage::turn_idregister,this,&MainWindow::turn4);
    connect(regis,&IDregister::return_page1,this,&MainWindow::turn1); 
    connect(login,&LoginPage::turn_page6,this,&MainWindow::turn5);
    connect(current,&CurrentPlayer::turn_page1,this,&MainWindow::turn1);
    connect(idlogin,&IdlogPage::log_succeed,this,&MainWindow::turn3);
    connect(idlogin,&IdlogPage::success_ID,ls,&Succeed::show_id);
    connect(ls,&Succeed::return_page1,this,&MainWindow::turn1);
    connect(regis,&IDregister::return_login,this,&MainWindow::turn1);

    connect(ls,&Succeed::open_game,this,&MainWindow::open_game);
    connect(current,&CurrentPlayer::Game_begin,this,&MainWindow::open_game);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//////主页转登陆页////////
void MainWindow::turn(){
    ui->stackedWidget->setCurrentIndex(1);
}
//////退出游戏/////////
void MainWindow::exit(){
    close();
}
//////转至主页面////////
void MainWindow::turnToMain(){
    ui->stackedWidget->setCurrentIndex(0);
}
//////账号登陆页面///////
void MainWindow::turn2(){
    ui->stackedWidget->setCurrentIndex(2);
}
//////转至登录页/////////
void MainWindow::turn1(){
    ui->stackedWidget->setCurrentIndex(1);
}
//////转至注册页面////////
void MainWindow::turn4(){
    ui->stackedWidget->setCurrentIndex(4);
}
//////转至登陆成功页面//////////
void MainWindow::turn3(){
    ui->stackedWidget->setCurrentIndex(3);
}
/////临时登陆Player界面////
void MainWindow::turn5(){
    ui->stackedWidget->setCurrentIndex(5);
}
/////跳转游戏///
void MainWindow::open_game(const QString &p1,const QString &p2){
    qDebug()<<p1<<p2;
    game_widget *game=new game_widget(nullptr,p1,p2);
    game->setWindowTitle("坦克大战");
    game->show();
    this->close();
}
