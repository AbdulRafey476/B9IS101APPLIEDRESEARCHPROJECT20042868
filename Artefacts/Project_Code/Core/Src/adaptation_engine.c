#include "adaptation_engine.h"

static ModelVariant current = STANDARD_INT8;

void AdaptationEngine_Init(void)
{
    current = STANDARD_INT8;
}

ModelVariant AdaptationEngine_Decide(HardwareState hw)
{
    (void)hw;
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