#include <inttypes.h>
#include "../include/io.h"
#include "../include/packet.h"

void send_data(const char* data) {
    read_data(data);
}

void read_data(const char* data) {
    packet_t *packet = (packet_t*)data;
    if (check_crc16(packet)) {
        printf("\nCRC16 check-sum OK!\n");
        printf("To: %"PRId16"\n", packet->payload.address);
        printf("Packet number: %"PRId16"\n", packet->payload.packet_number);
        printf("Instruction: %d\n", (int) packet->payload.instruction);
        printf("Temperature: %"PRId16"\n", packet->payload.data.temperature);
        printf("Wetness: %d\n", (int) packet->payload.data.wetness);
        printf("Speed of the wind: %"PRId16"\n", packet->payload.data.windspeed);
        printf("CRC16 check-sum: %"PRId16"\n", packet->check_sum);
    }
    else
        printf("\nCRC16 check-sum wrong!\n");

}