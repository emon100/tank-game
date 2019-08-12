#ifndef MY_MAP_H
#define MY_MAP_H
#include "mymap.h"

using namespace MAP;
mymap::mymap():
        mapplane{},//SET plane EMPTY
        spawn1(1,1),
        spawn2(mapsize-2,mapsize-2),
        base1(1,(mapsize/2)-1),
        base2(mapsize-2,(mapsize/2)-1),
        spawn1_direction(SOUTH),
        spawn2_direction(NORTH)
{

    init();
}

void mymap::init(){//初始化周围的墙壁
    for (size_t i=0;i<mapsize;++i) {
        mapplane[0][i]=IRON;
        mapplane[i][0]=IRON;
        mapplane[mapsize-1][i]=IRON;
        mapplane[i][mapsize-1]=IRON;
    }
    mapplane[static_cast<size_t>(base1.x())][static_cast<size_t>(base1.y())];
    mapplane[static_cast<size_t>(base2.x())][static_cast<size_t>(base2.y())];
    mapplane[static_cast<size_t>(spawn1.x())][static_cast<size_t>(spawn1.y())];
    mapplane[static_cast<size_t>(spawn2.x())][static_cast<size_t>(spawn2.y())];
}

#endif
