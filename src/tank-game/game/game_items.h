#ifndef GAME_ITEMS_H
#define GAME_ITEMS_H

#include <QObject>
#include <QGraphicsItem>
#include "map_maker/mymap.h"
enum TANK_PROPERTY{TANK_1,TANK_2};

class BULLET:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    BULLET();

    void setSpeed(int speed);
    int getSpeed() const;
/*
    void setMoveFlag(bool flag);
    bool getMoveFlag() const;
    */

    void setDirection(DIRECTION d){direction=d;}
    DIRECTION getDirection(){return direction;}
    //void getBulletStatus(QMatrix &matrixBullet, QImage &imgBullet);
    bool handleCollisions();

    bool isWall(int xx, int yy);
    bool attackWall();
    bool attackIron();
    bool attackEnemy(char role);
    bool attackBase();

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);

    QRectF boundingRect() const;

private:
    QImage current_img;
    int m_speed;
    DIRECTION direction;

signals:
    void destroy_item(QGraphicsItem *);
    void kill_tank(QGraphicsItem *);

};



class TANK:public QGraphicsItem
{
public:
    QPointF old_pos;
    bool tank_movable;
    bool   bullet_movable;
    BULLET bullet;
    explicit TANK(TANK_PROPERTY property=TANK_1);
    //void timerEvent(QTimerEvent *event);
    QRectF boundingRect() const;

    bool handleCollisions();
    inline int &speed(){return tank_speed;}
    inline void set_direction(DIRECTION dir){direction=dir;}
    inline DIRECTION get_direction(){return direction;}

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);


private:

    TANK_PROPERTY property;//坦克属性
    int tank_speed;//坦克速度
    DIRECTION direction;//坦克方向
    QImage current_img;

signals:

public slots:
};




class MAP_ITEM: public QGraphicsItem
{
public:
    explicit MAP_ITEM(MAP_OBJECT item=AIR);
    int health;

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);

    QRectF boundingRect() const;

private:
    MAP_OBJECT property;
    QImage current_img;
};

#endif // GAME_ITEMS_H
