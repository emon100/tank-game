#ifndef MAP_H
#define MAP_H
#include <QPoint>
#include <QImage>
#include <array>
const QImage IronImg(":/images/iron.bmp");
const QImage Base1Img(":/images/Tank.ico");
const QImage Base2Img(":/images/Tank.ico");

const int mapsize=16;

enum MAP_OBJECT{NONE=-1,AIR=0,IRON,BRICK,BASE1,BASE2};
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
    mymap(MAP_OBJECT (*a)[64]);
    mymap();
    //使用默认复制构造函数
private:
    void init();
    void init(MAP_OBJECT (*a)[64]);
};
}


#endif // MAP_H
