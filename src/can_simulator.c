#include <stdio.h>
#include <stdint.h>




typedef struct {
    uint16_t id;
    uint8_t dlc;
    uint8_t data[8];
    } CAN_Message;


void printCAN(CAN_Message msg) {
    printf("ID: 0x%X | Data:", msg.id);
    for (int i = 0; i < msg.dlc; i++) {
        printf(" %d", msg.data[i]);
        }
    printf("\n");
}


void main(){
    CAN_Message socMsg = { .id = 0x101, .dlc = 2, .data = {75, 0} }; // 75% SOC
    printCAN(socMsg);

    
}


