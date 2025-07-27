#include <stdio.h>
#include <unistd.h>  // for sleep()

// Define Your Battery Specs
#define BATTERY_CAPACITY_AH    2.2f         // 10Ah battery
#define BATTERY_CAPACITY_AS     (BATTERY_CAPACITY_AH * 3600.0f)


// Initialize State Variables
float soc = 1.0f;           // Start fully charged



// Write the SoC Update Function

void SOC_Estimator_Update(float current, float dt) {
   float delta_soc = (current * dt) / BATTERY_CAPACITY_AS;

    soc -= delta_soc;

     // Clamp SOC between 0 and 1
    if (soc > 1.0f) soc = 1.0f;
    if (soc < 0.0f) soc = 0.0f;

   
}



int main() {
    float current = 1.0f;  // Simulate 1A discharge
    float dt = 1.0f;       // 1-second interval

    for (int t = 0; t < 3600; t++) {  // Simulate 1 hour
        SOC_Estimator_Update(current, dt);
        printf("Time: %d sec | SoC: %.2f%%\n", t, soc * 100.0f);
        sleep(1);
    }

    return 0;
}