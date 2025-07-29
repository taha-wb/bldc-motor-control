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

// simulate current values

void Simulate_Profile(float* profile, int size, float dt){
    for (int t = 0; t < size; t++){
        float current = profile[t];
        SOC_Estimator_Update(current, dt);
        printf("Time: %d sec | Current: %.2f A | SoC: %.2f%%\n", t, current, soc * 100.0f);
        sleep(1);
    }
}



int main() {
      // Profile 1: Alternating load (e.g., city driving)
    float current_profile1[10] = {0.5f, 1.0f, 2.0f, -0.5f, -1.0f, 0.0f, 1.5f, 0.0f, -2.0f, 0.5f};

    float dt = 1.0f;       // 1-second interval

    for (int t = 0; t < 3600; t++) {  // Simulate 1 hour
       
        printf("=== Simulating Current Profile 1 ===\n");
        Simulate_Profile(current_profile1, 10, dt);
    }

    return 0;
}