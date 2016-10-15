#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "../include/packet.h"
#include "../include/io.h"

#define ADDRESS 4
#define INSTRUCTION 0x01

int main(void) {

    uint8_t packet_count = 1;

    weather_data_t data;
    printf("Enter data:\n");
    printf("Temperature: ");
    scanf("%"SCNd16, &data.temperature);
    printf("Wetness: ");
    scanf("%"SCNd8, &data.wetness);
    printf("Speed of the wind: ");
    scanf("%"SCNd16, &data.windspeed);

    packet_t packet;
    make_packet(&packet, ADDRESS, packet_count, INSTRUCTION, data);

    send_data((char*)&packet);
    packet_count++;

    return 0;
}