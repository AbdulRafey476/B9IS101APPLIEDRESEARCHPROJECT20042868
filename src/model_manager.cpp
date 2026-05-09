#include "model_manager.h"

// Model storage + switching layer of system
// Placeholder model blobs.
// In real implementation, replace with .tflite arrays converted to C headers.
static const unsigned char g_standard_int8_model[] = {0x01, 0x02, 0x03};
static const unsigned char g_pruned_model[] = {0x04, 0x05, 0x06};
static const unsigned char g_mixed_precision_model[] = {0x07, 0x08, 0x09};

void ModelManager::init() {
    standard_int8_ = {"Standard INT8", g_standard_int8_model, sizeof(g_standard_int8_model)};
    pruned_ = {"Pruned Variant", g_pruned_model, sizeof(g_pruned_model)};
    mixed_precision_ = {"Mixed Precision", g_mixed_precision_model, sizeof(g_mixed_precision_model)};
    current_ = standard_int8_;
}

void ModelManager::switchTo(ModelVariant variant) {
    switch (variant) {
        case ModelVariant::STANDARD_INT8:
            current_ = standard_int8_;
            break;
        case ModelVariant::PRUNED_VARIANT:
            current_ = pruned_;
            break;
        case ModelVariant::MIXED_PRECISION:
            current_ = mixed_precision_;
            break;
    }
}

const ModelDescriptor& ModelManager::currentModel() const {
    return current_;
}
