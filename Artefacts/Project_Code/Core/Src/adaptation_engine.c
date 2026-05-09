#include "adaptation_engine.h"

static ModelVariant current = STANDARD_INT8;
static int robustModeActive = 0;

void AdaptationEngine_Init(void)
{
    current = STANDARD_INT8;
    robustModeActive = 0;
}

ModelVariant AdaptationEngine_Decide(HardwareState hw)
{
    /*
     * Calibrated for current STM32 board range:
     * Temp observed: ~63–68C
     * Vcc observed: ~3.00V
     * CPU observed: ~44–70%
     */

    // Robust / thermal / high-load condition
    if ((hw.temperature_c > 66.8f) || (hw.cpu_load_percent > 64.0f) || (hw.vcc_volts < 2.98f))
    {
        robustModeActive = 1;
        current = MIXED_PRECISION;
        return current;
    }

    // Hysteresis exit from robust mode
    if (robustModeActive &&
        hw.temperature_c < 65.8f &&
        hw.cpu_load_percent < 58.0f &&
        hw.vcc_volts > 2.99f)
    {
        robustModeActive = 0;
    }

    if (robustModeActive)
    {
        current = MIXED_PRECISION;
        return current;
    }

    // Low/normal load and stable condition
    if ((hw.cpu_load_percent < 50.0f) && (hw.vcc_volts >= 3.00f))
    {
        current = STANDARD_INT8;
        return current;
    }

    // Moderate load / borderline voltage condition
    if ((hw.cpu_load_percent >= 50.0f) || (hw.vcc_volts < 3.01f))
    {
        current = PRUNED_VARIANT;
        return current;
    }

    current = STANDARD_INT8;
    return current;
}

const char* AdaptationEngine_ToString(ModelVariant variant)
{
    switch (variant)
    {
        case STANDARD_INT8:
            return "STANDARD_INT8";

        case PRUNED_VARIANT:
            return "PRUNED_VARIANT";

        case MIXED_PRECISION:
            return "MIXED_PRECISION";

        default:
            return "UNKNOWN";
    }
}
