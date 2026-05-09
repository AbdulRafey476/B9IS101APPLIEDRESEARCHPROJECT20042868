#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "adaptation_engine.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char* name;
    const unsigned char* model_data;
    uint32_t model_size;
} ModelDescriptor;

void ModelManager_Init(void);
void ModelManager_SwitchTo(ModelVariant variant);
ModelDescriptor ModelManager_CurrentModel(void);

bool ModelManager_TFLM_Init(void);
bool ModelManager_RunInference(float temp, float cpu);
float ModelManager_GetOutput(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif
