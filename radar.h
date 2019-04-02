#ifndef RADAR_DATA
#define RADAR_DATA
#include<stdint.h>
struct target_info{
int distance=10;
int16_t angle=30;
int y=6;
int x=8;
int16_t speed=100;
int8_t power=20;
};
struct radar_data
{
int16_t header=0x55AA;
int8_t address=0x12;
int16_t length=0x0204;
int8_t targetcount=0x3;
target_info targets[3];
int8_t sum=0x11;
};
#endif