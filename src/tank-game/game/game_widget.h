#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimer>
#include <QPair>
#include "map_maker/mymap.h"
#include "game/game_items.h"

namespace Ui {
class game_widget;
}

class game_widget : public QWidget
{
    Q_OBJECT

public:
    explicit game_widget(QWidget *parent = nullptr,const QString &p1_n="player1",const QString &p2_n="player2");
    ~game_widget();
    void close();
protected:
    void initSceneView();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


private:
    Ui::game_widget *ui;
    QTimer timer;
    bool ispause;
    QGraphicsScene  *scene;//场景
    QGraphicsView   *view;//视图
    MAP::mymap map;//地图文件
    TANK *p1;
    TANK *p2;
    //QVector<int> score;
    //两人nam
    QString p1_name;
    QString p2_name;
    //两人score
    int p1_score;
    int p2_score;
    int p1_lives;
    int p2_lives;



    void game_ui_update();
    void open();
    void open_with_path(const QString &path);
    void object_update();
    void tanks_update();
    void bullets_update();

    void set_map_items();
    void spawn_tanks();
    void spawn_tank1();
    void spawn_tank2();
    void fire_bullet1();
    void fire_bullet2();
    void kill_tank(QGraphicsItem *tank);
    void p1_destroy(QGraphicsItem *tank);
    void p2_destroy(QGraphicsItem *tank);

    void final(int n);
    void init();
    void safe_close();
signals:
    void win(int n);
private slots:
    void on_LevelButton_clicked();
    void on_IntroButton_clicked();
    void on_PauseButton_clicked();
};

#endif // GAME_WIDGET_H
