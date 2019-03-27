//
// Created by yangwei on 3/27/19.
//
#ifndef RADAR_TCP_RADAR_DATA_H
#define RADAR_TCP_RADAR_DATA_H

#include <iostream>
struct target_info{
    int distance;
    int16_t angle;
    int y;
    int x;
    int16_t speed;
    int8_t power;
};
struct radar_data
{
    int16_t header;
    int8_t address;
    int16_t length;
    int8_t targetcount;
    target_info targets[30];
    int8_t sum;
};
#endif //RADAR_TCP_RADAR_DATA_H
