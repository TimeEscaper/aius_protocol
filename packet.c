#include <inttypes.h>
#include "packet.h"

uint16_t get_crc16(const payload_t* payload) {
    size_t payload_size = sizeof(payload);
    uint16_t result = 0xFFFF;
    uint8_t *payload_chr = (uint8_t*)payload;
    unsigned short i;

    while (payload_size--) {
        result ^= *payload_chr++ << 8;
        for (i = 0; i < 8; i++)
            result = result & (uint16_t )0x8000 ? (result << (uint16_t )1) ^ (uint16_t )0x1021 : result << (uint16_t )1;
    }

    return result;
}

uint8_t check_crc16(const packet_t* packet) {
    uint16_t check_sum = get_crc16(&packet->payload);
    if (check_sum == packet->check_sum)
        return 1;
    return 0;
}

void make_packet(packet_t *packet,
                 uint16_t address,
                 uint16_t packet_number,
                 uint8_t instruction,
                 weather_data_t data)
{
    payload_t payload;
    payload.address = address;
    payload.packet_number = packet_number;
    payload.instruction = instruction;
    payload.data = data;
    uint16_t check_sum = get_crc16(&payload);
    packet->payload = payload;
    packet->check_sum = check_sum;
}
