#ifndef STRUCT_SENSOR_H
#define STRUCT_SENSOR_H

#include "../Utils/road_time.h"

typedef struct
{
    int pulsosEsquerda;
    int pulsosDireita;
    int pulsosTras;
    int estercamento;
    road_time_t time;
}Sensors;




#endif