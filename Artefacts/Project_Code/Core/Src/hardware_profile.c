#include "hardware_profile.h"

static HardwareState state;

void HardwareProfiler_Init(void)
{
    state.temperature_c = 25.0f;
    state.vcc_volts = 3.30f;
    state.cpu_load_percent = 10.0f;
}

void HardwareProfiler_Sample(void)
{
}

HardwareState HardwareProfiler_GetState(void)
{
    return state;
}