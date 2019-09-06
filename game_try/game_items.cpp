#include "game_items.h"
#include <QPainter>
#include <QRectF>
#include <QDebug>
BULLET::BULLET():
    current_img(BulletImg),
    m_speed(4)
{

}

void BULLET::setSpeed(int speed)
{
    m_speed = speed;
}

int BULLET::getSpeed() const
{
    return m_speed;
}
/*
void BULLET::setMoveFlag(bool flag)
{
    m_moveFlag = flag;
}
bool BULLET::getMoveFlag() const
{
    return m_moveFlag;
}
*/

QRectF BULLET::boundingRect() const{
    return QRectF(-5,-8,10,16);
}

bool BULLET::handleCollisions(){
    auto cols = collidingItems(Qt::IntersectsItemBoundingRect);
    bool ok=true;
    for (auto x : cols) {
        if(x->data(0) == IRON){
            ok=false;
            if(this->data(0)==10)
                emit destroy_item(x);
            else {
                emit destroy_item(x);
            }
            break;
        }else if (x->data(0) == BRICK) {

            ok = false;
            emit kill_tank(x);
            break;
    }
    }
    if(ok){
        qDebug()<<"OK";
        return true;
    }else {
        qDebug()<<"Boom";
        return false;
    }


}

void BULLET::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    QRectF temp=boundingRect();
    switch(direction){
    case NORTH: painter->rotate(0);break;
    case WEST : painter->rotate(270);break;
    case SOUTH: painter->rotate(180);break;
    case EAST : painter->rotate(90);break;
    }
    painter->drawImage(temp.topLeft(),current_img);
    //painter->setPen(Qt::white);
    //painter->drawRect(boundingRect());
}

/*下为坦克部件*/
TANK::TANK(TANK_PROPERTY pro) :
    tank_movable(false),
    bullet_movable(false),
    property(pro),
    tank_speed(3)
{
    if(property==TANK_1){
        current_img=P1TankImg.scaledToWidth(32);
        bullet.setData(0,10);
    }else {
        current_img=P2TankImg.scaledToWidth(32);
        bullet.setData(0,20);
    }
    setData(0,BRICK);

}

QRectF TANK::boundingRect() const{
    qreal adjust = 1;
    //on purpose to make both be width
    return QRectF(-current_img.width()/2,-current_img.width()/2,
                  current_img.width()-adjust*2,current_img.width()-adjust*2);
}

void TANK::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF temp=boundingRect();
    switch(direction){
    case NORTH: painter->rotate(0);break;
    case WEST : painter->rotate(270);break;
    case SOUTH: painter->rotate(180);break;
    case EAST : painter->rotate(90);break;
    }
    painter->drawImage(temp.topLeft(),current_img);
    //painter->setPen(Qt::white);
    //painter->drawRect(boundingRect());
}

bool TANK::handleCollisions(){
    auto cols = collidingItems(Qt::IntersectsItemBoundingRect);
    bool ok=true;
    for (auto x : cols) {
        if(x->data(0) == IRON){
            ok=false;
            break;
        }else if(x->data(0)== BRICK){
            ok=false;
            break;
        }
    }
    if(ok){
        qDebug()<<"OK";
        return true;
    }else {
        qDebug()<<"Boom";
        return false;
    }

}


/*下为地图部件*/
MAP_ITEM::MAP_ITEM(MAP_OBJECT prop):
    property(prop)
{
    bool air=false;
    switch(property){
    case BRICK :current_img=BrickImg;break;
    case IRON  :current_img=IronImg;break;
    case BASE1 :current_img=Base1Img;break;
    case BASE2 :current_img=Base2Img;break;
    case SPAWN1:
    case SPAWN2:
    case NONE  :
    case AIR   :air=true;current_img=AirImg.scaledToWidth(32);break;
    }
    if(air){
        setData(0,AIR);
    }else {
        setData(0,IRON);
    }
    if(property==BASE1){
        setData(1,1);

    }else if(property==BASE2){
        setData(1,2);
}
}

void MAP_ITEM::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QRectF temp=boundingRect();
    painter->drawImage(temp.topLeft(),current_img,QRectF(temp.topLeft(),QSizeF(BLOCK_SIZE,BLOCK_SIZE)));
   // painter->setPen(Qt::blue);
    //painter->drawRect(boundingRect());
}

QRectF MAP_ITEM::boundingRect() const{
    return QRectF(0,0,32,32);
}
