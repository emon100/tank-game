#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
//wriiten by JHN
#include "string.h"
#include "J_mainpage.h"
#include "J_loginpage.h"
#include "J_idlogpage.h"
#include "J_succeed.h"
#include "J_idregister.h"
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
    ~MainWindow();

private slots:
    void open_game(const QString &p1, const QString &p2);
private:
    Ui::MainWindow *ui;
    QString Player1;
    QString Player2;
};

#endif // MAINWINDOW_H
