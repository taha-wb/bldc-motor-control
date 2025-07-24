#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simulated system API
void logEvent(const char *message) {
    time_t now = time(NULL);
    printf("[LOG %s] %s\n", strtok(ctime(&now), "\n"), message);
}

void enterProtectionMode() {
    logEvent("🚨 Entering protection mode!");
}

// Utility to combine 2 bytes into 16-bit integer
uint16_t toUint16(uint8_t high, uint8_t low) {
    return (high << 8) | low;
}

// Fault injection interface
void simulate_fault(const char *fault_type) {
    if (strcmp(fault_type, "battery_overtemp") == 0) {
        float temp = 65.0;  // degrees Celsius
        logEvent("⚠️ Simulating battery over-temperature...");
        if (temp > 60.0) {
            logEvent("Battery temperature critical: 65°C");
            enterProtectionMode();
        }

    } else if (strcmp(fault_type, "motor_overspeed") == 0) {
        int rpm = 10500;
        logEvent("⚠️ Simulating motor over-speed...");
        if (rpm > 10000) {
            logEvent("Motor RPM exceeded safe limit: 10500");
            enterProtectionMode();
        }

    } else if (strcmp(fault_type, "low_voltage") == 0) {
        int voltage = rand() % 40 + 240;  // Simulate 240–280V
        logEvent("⚠️ Simulating low voltage...");
        printf("Simulated voltage: %dV\n", voltage);
        if (voltage < 280) {
            logEvent("Battery voltage too low. Entering safe mode.");
            enterProtectionMode();
        }

    } else if (strcmp(fault_type, "can_timeout") == 0) {
        logEvent("⚠️ Simulating CAN timeout...");
        logEvent("No message from sensor ECU > 1s");
        logEvent("Setting sensor_offline fault flag");
        enterProtectionMode();

    } else if (strcmp(fault_type, "sensor_drift") == 0) {
        logEvent("⚠️ Simulating sensor drift...");
        int current = 100;
        for (int i = 0; i < 5; i++) {
            current += 50;
            printf("Simulated current: %dA\n", current);
            if (current > 250) {
                logEvent("Sensor reading abnormal: current drift > 250A");
                enterProtectionMode();
                break;
            }
        }

    } else {
        printf("❌ Unknown fault type: %s\n", fault_type);
    }
}


int main() {
    simulate_fault("battery_overtemp");
    simulate_fault("motor_overspeed");
    simulate_fault("low_voltage");
    simulate_fault("can_timeout");
    simulate_fault("sensor_drift");

    return 0;
}