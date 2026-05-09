#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

typedef struct {
    float temperature_c;
    float vcc_volts;
    float cpu_load_percent;
} HardwareState;

void HardwareProfiler_Init(void);
void HardwareProfiler_Sample(void);
HardwareState HardwareProfiler_GetState(void);

#endif
