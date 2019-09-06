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
    mapplane[1][mapsize/2 -1]=BASE1;
    mapplane[mapsize-2][mapsize/2 -1]=BASE2;
}

#endif
