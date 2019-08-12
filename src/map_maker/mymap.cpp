#ifndef MY_MAP_H
#define MY_MAP_H
#include "mymap.h"

using namespace MAP;
mymap::mymap():
        mapplane{},//SET plane EMPTY
        spawn1(QPoint(1,1)),
        spawn2(QPoint(mapsize-2,mapsize-2)),
        base1(QPoint(1,(mapsize/2)-1)),
        base2(QPoint(mapsize-2, (mapsize/2) -1)),
        spawn1_direction(SOUTH),
        spawn2_direction(NORTH)
{

    init();
}

mymap::mymap(MAP_OBJECT (*a)[64]){
    init(a);
}

void mymap::init(){//初始化周围的墙壁
    for (size_t i=0;i<mapsize;++i) {
        mapplane[0][i]=IRON;
        mapplane[i][0]=IRON;
        mapplane[mapsize-1][i]=IRON;
        mapplane[i][mapsize-1]=IRON;
    }

}

void mymap::init(MAP_OBJECT (*a)[64]){
    for (size_t i=0;i<mapsize;++i) {
        for (size_t j=0;j<mapsize;++j) {
            mapplane[i][j]=a[i][j];
        }
    }
}

#endif
