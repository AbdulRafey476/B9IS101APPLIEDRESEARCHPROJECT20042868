#include "adaptation_engine.h"

static ModelVariant current = STANDARD_INT8;

void AdaptationEngine_Init(void)
{
    current = STANDARD_INT8;
}

ModelVariant AdaptationEngine_Decide(HardwareState hw)
{
    /*
     * Calibrated for current STM32 board range:
     * Temp observed: ~63–68C
     * Vcc observed: ~3.00V
     * CPU observed: ~44–70%
     */

    if ((hw.temperature_c > 66.8f) || 
        (hw.cpu_load_percent > 64.0f) || 
        (hw.vcc_volts < 2.98f))
    {
        current = MIXED_PRECISION;
        return current;
    }

    if ((hw.cpu_load_percent < 50.0f) && (hw.vcc_volts >= 3.00f))
    {
        current = STANDARD_INT8;
        return current;
    }

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