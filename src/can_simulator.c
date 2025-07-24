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
    CAN_Message batteryPackStatus = {.id = 	0x180 ,.dlc = 4, .data = {0x50, 0x01, 0x00, 0x00}};  // Battery Pack Info Message


    // battery temp logic
    CAN_Message batteryTemp = {.id = 0x180 ,.dlc = 8, .data =  {0x01, 0x90, 0, 0, 0, 0, 0, 0}};

    uint16_t raw_temp = (batteryTemp.data[0] << 8) | batteryTemp.data[1] ;
    float battery_temp = ((float)raw_temp) /10.0;


    // validate & respond

    
    if (battery_temp > 60.0) {
    // 🔴 Over-temperature
    triggerCoolingSystem();
    logEvent("Battery temp high");
    } else if (battery_temp < 0.0) {
    // 🟡 Too cold
    restrictCharging();
    logEvent("Battery temp low");
    } else {
    // ✅ Normal
    updateDisplay(battery_temp);
    }



    // motor RPM logic 
    CAN_Message motorRpm = {.id = 0x220 ,.dlc = 8, .data = {0x13, 0x88, 0, 0, 0, 0, 0, 0}};
    uint16_t raw_rpm = (motorRpm.data[0] << 8) | motorRpm.data[1];
    int motor_rpm = (int) raw_rpm;


    // validate & respond

    if (motor_rpm > 10000) {
    logEvent("Over-speed detected");
    enterProtectionMode();  // cut power, flag warning
    } else if (motor_rpm < 0) {
    logEvent("Invalid RPM value");  // should never happen with unsigned
    } else {
    updateDisplayRPM(motor_rpm);
    }



    
    printCAN(socMsg);
    printCAN(batteryPackStatus);
   

    
}


