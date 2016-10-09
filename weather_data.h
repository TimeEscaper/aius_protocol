#ifndef AIUS_PROTOCOL_WEATHER_DATA_H_H
#define AIUS_PROTOCOL_WEATHER_DATA_H_H

#include <stdint.h>

typedef struct {
    uint16_t temperature;
    uint8_t wetness;
    uint16_t windspeed;
} weather_data_t;

#endif //AIUS_PROTOCOL_WEATHER_DATA_H_H
