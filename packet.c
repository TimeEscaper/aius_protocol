#include <inttypes.h>
#include "packet.h"

uint16_t get_crc16(packet_t* packet) {
    struct no_crc_packet_t {
        uint16_t address;
        uint16_t packet_number;
        uint8_t instruction;
        weather_data_t data;
    } no_crc_packet;
    no_crc_packet.address = packet->address;
    no_crc_packet.instruction = packet->instruction;
    no_crc_packet.packet_number = packet->packet_number;
    no_crc_packet.data = packet->data;
    size_t packet_size = sizeof(no_crc_packet);
    uint16_t result = 0xFFFF;
    uint8_t *packet_chr = (uint8_t *)&no_crc_packet;
    unsigned short i;

    while (packet_size--) {
        result ^= *packet_chr++ << 8;
        for (i = 0; i < 8; i++)
            result = result & (uint16_t )0x8000 ? (result << (uint16_t )1) ^ (uint16_t )0x1021 : result << (uint16_t )1;
    }

    return result;
}

uint8_t check_crc16(packet_t *packet) {
    uint16_t check_sum = get_crc16(packet);
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
    packet->address = address;
    packet->packet_number = packet_number;
    packet->instruction = instruction;
    packet->data = data;
    uint16_t check_sum = get_crc16(packet);
    packet->check_sum = check_sum;
}
