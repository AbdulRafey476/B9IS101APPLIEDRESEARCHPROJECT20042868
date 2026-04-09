#include "hardware_profile.h"

// NOTE:
// This is project-style demonstration code aligned with the dissertation.
// ADC / DWT register reads are represented as placeholders so you can adapt
// them inside STM32CubeIDE for your exact STM32L475 board.

void HardwareProfiler::init() {
    state_.temperature_c = 25.0f;
    state_.vcc_volts = 3.3f;
    state_.cpu_load_percent = 10.0f;
}

void HardwareProfiler::sample() {
    state_.temperature_c = movingAverage(state_.temperature_c, readTemperatureSensor(), 0.2f);
    state_.vcc_volts = movingAverage(state_.vcc_volts, readVcc(), 0.2f);
    state_.cpu_load_percent = movingAverage(state_.cpu_load_percent, readCpuLoad(), 0.2f);
}

HardwareState HardwareProfiler::getState() const {
    return state_;
}

float HardwareProfiler::readTemperatureSensor() {
    // TODO: Replace with ADC1_IN16 read + calibration formula
    return 68.0f;
}

float HardwareProfiler::readVcc() {
    // TODO: Replace with VREFINT conversion logic
    return 2.95f;
}

float HardwareProfiler::readCpuLoad() {
    // TODO: Replace with DWT->CYCCNT based estimation
    return 57.0f;
}

float HardwareProfiler::movingAverage(float previous, float current, float alpha) {
    // Exponential Moving Average (EMA).
    // y=αxcurrent+(1−α)xprevious
    // alpha = 0.2 20% new value 80% old value
    // changes happen gradually, not abruptly
    return (alpha * current) + ((1.0f - alpha) * previous);
}
