#ifndef MAP_H
#define MAP_H
#include <QPoint>
#include <QImage>
#include <array>
const QImage IronImg(":/resources/iron.bmp");
const QImage BrickImg(":/resources/brick.bmp");
const QImage Base1Img(":/resources/base1.bmp");
const QImage Base2Img(":/resources/base2.bmp");
const QImage Spawn1Img(":/resources/spawn1.bmp");
const QImage Spawn2Img(":/resources/spawn2.bmp");

const int mapsize=16;

enum MAP_OBJECT{NONE=-1,AIR=0,IRON,BRICK,BASE1,BASE2,SPAWN1,SPAWN2};
enum DIRECTION{EAST=0,SOUTH,WEST,NORTH};

namespace MAP {

using std::array;
class mymap{
public:
    array<array<MAP_OBJECT,mapsize>,mapsize> mapplane;//地图平面
    QPoint spawn1;//出生点，基地以及出生点朝向
    QPoint spawn2;
    QPoint base1;
    QPoint base2;
    DIRECTION spawn1_direction;
    DIRECTION spawn2_direction;
    mymap();
    //使用默认复制构造函数
private:
    void init();
};
}


#endif // MAP_H
