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


#endif
