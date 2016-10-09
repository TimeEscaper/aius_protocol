#ifndef AIUS_PROTOCOL_PACKET_H_H
#define AIUS_PROTOCOL_PACKET_H_H

#include <stdint.h>
#include <malloc.h>
#include "weather_data.h"

typedef struct {
    uint16_t address;
    uint16_t packet_number;
    uint8_t instruction;
    weather_data_t data;
    uint16_t check_sum;
} packet_t;


uint16_t get_crc16(packet_t* packet);
/*
* https://ru.wikibooks.org/wiki/Реализации_алгоритмов/Циклический_избыточный_код
* Name  : CRC-16 CCITT
* Poly  : 0x1021    x^16 + x^12 + x^5 + 1
* Init  : 0xFFFF
* Revert: false
* XorOut: 0x0000
* Check : 0x29B1 ("123456789")
* MaxLen: 4095 байт (32767 бит) - обнаружение одинарных, двойных, тройных и всех нечетных ошибок
*/

uint8_t check_crc16(packet_t* packet);

void make_packet(packet_t *packet,
                           uint16_t address,
                           uint16_t packet_number,
                           uint8_t instruction,
                           weather_data_t data);


#endif //AIUS_PROTOCOL_PACKET_H_H
