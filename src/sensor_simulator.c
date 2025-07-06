#include <stdio.h>
#include <stdlib.h>
#include <time.h>



float simulate_voltage(){
    return 3.5 + ((rand() % 100 ) / 1000.0);  // 3.5v - 3.6v

}

float simulate_current(){
    return 1.0 + ((rand() % 200 ) / 100.0);  // 1.0A - 3.0A
    
}

float simulate_temp(){
    return 30.0 + ((rand() % 150 ) / 10.0);  // 30-45 C
    
}


int main(){
    srand(time(NULL)); // to avoid same random values

    float V = simulate_voltage();
    float I = simulate_current();
    float T = simulate_temp();


    printf("V=%.2fV | I=%.2fA | T=%.1fC\n",V,I,T);
    if (V > 4.2 || V < 2.5) printf("Voltage Out of Range!\n");
    if (T > 60.0) printf("Overtemperature!\n");
    return 0;
}




