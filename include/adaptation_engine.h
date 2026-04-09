#ifndef ADAPTATION_ENGINE_H
#define ADAPTATION_ENGINE_H

#include "hardware_profile.h"

enum class ModelVariant {
    STANDARD_INT8,
    PRUNED_VARIANT,
    MIXED_PRECISION
};

class AdaptationEngine {
public:
    AdaptationEngine();
    ModelVariant decide(const HardwareState& hw);
    const char* toString(ModelVariant variant) const;

private:
    ModelVariant current_;
    bool robustModeActive_;
};

#endif
