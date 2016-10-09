#include <stdint.h>
#include <inttypes.h>
#include "stdio.h"
#include "packet.h"
#include "weather_data.h"
#include "io.h"

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

    int res = send_data((char*)&packet);
    packet_count++;

    char* received_data = (char*)malloc(sizeof(char));
    read_data(received_data);
    free(received_data);

    if (check_crc16(&packet))
        printf("\nCRC16 check-sum OK!\n");
    else
        printf("\nCRC16 check-sum wrong!\n");

    printf("To: %"PRId16"\n", packet.address);
    printf("Packet number: %"PRId16"\n", packet.packet_number);
    printf("Instruction: %d\n", (int)packet.instruction);
    printf("Temperature: %"PRId16"\n", packet.data.temperature);
    printf("Wetness: %d\n", (int)packet.data.wetness);
    printf("Speed of the wind: %"PRId16"\n", packet.data.windspeed);
    printf("CRC16 check-sum: %"PRId16"\n", packet.check_sum);

    return 0;
}