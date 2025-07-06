





int main() {
    float soc = 50.0;
    float current = 2.0; // Amps
    float dt = 1.0; // Seconds
    float capacity = 50.0; // Ah
    soc = updateSOC(soc, current, dt, capacity);
    printf("Updated SOC: %.2f%%\n", soc);
    return 0;
}