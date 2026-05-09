#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#include <stdint.h>

struct HardwareState {
    float temperature_c;
    float vcc_volts;
    float cpu_load_percent;
};

class HardwareProfiler {
public:
    void init();
    void sample();
    HardwareState getState() const;

private:
    HardwareState state_;
    float readTemperatureSensor();
    float readVcc();
    float readCpuLoad();
    float movingAverage(float previous, float current, float alpha);
};

#endif
