#include "model_manager.h"

void ModelManager_Init(void) {}

void ModelManager_SwitchTo(ModelVariant variant)
{
    (void)variant;
}

ModelDescriptor ModelManager_CurrentModel(void)
{
    ModelDescriptor d = {0};
    return d;
}

bool ModelManager_TFLM_Init(void)
{
    return false;
}

bool ModelManager_RunInference(float temp, float cpu)
{
    (void)temp;
    (void)cpu;
    return false;
}

float ModelManager_GetOutput(uint8_t index)
{
    (void)index;
    return 0.0f;
}