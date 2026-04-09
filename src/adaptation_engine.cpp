#include "adaptation_engine.h"

AdaptationEngine::AdaptationEngine()
    : current_(ModelVariant::STANDARD_INT8), robustModeActive_(false) {}

ModelVariant AdaptationEngine::decide(const HardwareState& hw) {
    // Hysteresis-based switching logic
    if ((hw.temperature_c > 75.0f) || (hw.vcc_volts < 2.9f)) {
        robustModeActive_ = true;
        current_ = ModelVariant::MIXED_PRECISION;
        return current_;
    }

    if (robustModeActive_ && hw.temperature_c < 65.0f && hw.vcc_volts > 3.0f) {
        robustModeActive_ = false;
    }

    if (hw.cpu_load_percent > 85.0f) {
        current_ = ModelVariant::STANDARD_INT8;
        return current_;
    }

    if (robustModeActive_) {
        current_ = ModelVariant::MIXED_PRECISION;
        return current_;
    }

    if (hw.vcc_volts < 3.0f) {
        current_ = ModelVariant::PRUNED_VARIANT;
        return current_;
    }

    current_ = ModelVariant::STANDARD_INT8;
    return current_;
}

const char* AdaptationEngine::toString(ModelVariant variant) const {
    switch (variant) {
        case ModelVariant::STANDARD_INT8: return "STANDARD_INT8";
        case ModelVariant::PRUNED_VARIANT: return "PRUNED_VARIANT";
        case ModelVariant::MIXED_PRECISION: return "MIXED_PRECISION";
        default: return "UNKNOWN";
    }
}
