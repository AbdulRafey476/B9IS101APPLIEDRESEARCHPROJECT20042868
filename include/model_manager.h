#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "adaptation_engine.h"
#include <stdint.h>

struct ModelDescriptor {
    const char* name;
    const unsigned char* model_data;
    uint32_t model_size;
};

class ModelManager {
public:
    void init();
    void switchTo(ModelVariant variant);
    const ModelDescriptor& currentModel() const;

private:
    ModelDescriptor standard_int8_;
    ModelDescriptor pruned_;
    ModelDescriptor mixed_precision_;
    ModelDescriptor current_;
};

#endif
