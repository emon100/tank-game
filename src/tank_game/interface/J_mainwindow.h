#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
//wriiten by JHN
#include "J_mainpage.h"
#include "J_loginpage.h"
#include "J_idlogpage.h"
#include "J_succeed.h"
#include "J_idregister.h"
#include "J_players.h"
#include "J_currentplayer.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void turn();
    void exit();
    void turnToMain();
    void turn2();
    void turn1();
    void turn3();
    void turn4();
    void turn5();
    void turn6();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

extern      QString ID;//登陆账号
extern      QString Password;//登陆密码
extern      QString new_ID;//注册账号
extern      QString new_Password;//注册密码
extern      QString Player1;
extern      QString Player2;

#endif // MAINWINDOW_H
