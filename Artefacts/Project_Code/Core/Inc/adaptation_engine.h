#ifndef ADAPTATION_ENGINE_H
#define ADAPTATION_ENGINE_H

#include "hardware_profile.h"

typedef enum {
    STANDARD_INT8 = 0,
    PRUNED_VARIANT,
    MIXED_PRECISION
} ModelVariant;

void AdaptationEngine_Init(void);
ModelVariant AdaptationEngine_Decide(HardwareState hw);
const char* AdaptationEngine_ToString(ModelVariant variant);

#endif
