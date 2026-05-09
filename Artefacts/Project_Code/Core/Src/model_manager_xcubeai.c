/*
 * model_manager_xcubeai.c
 * X-CUBE-AI 10.2.0 inference — STM32F407
 * Model: Dense(2→16→3) float32
 * Classes: STANDARD_INT8=0, PRUNED_VARIANT=1, MIXED_PRECISION=2
 */

#include "model_manager.h"
#include "main.h"
#include <string.h>

#include "network.h"
#include "network_data.h"

extern UART_HandleTypeDef huart2;

static void uart_print(const char* msg)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

AI_ALIGNED(4) static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];
static const ai_handle act_ptrs[1] = { (ai_handle)activations };

static ai_handle  network_handle = AI_HANDLE_NULL;
static int        init_done      = 0;

static ai_buffer *ai_input  = NULL;
static ai_buffer *ai_output = NULL;

bool ModelManager_TFLM_Init(void)
{
    if (init_done) return true;

    uart_print("AI Init...\r\n");

    ai_error err = ai_network_create_and_init(
        &network_handle, act_ptrs, NULL);

    if (err.type != AI_ERROR_NONE || network_handle == AI_HANDLE_NULL) {
        uart_print("ERROR: AI init failed\r\n");
        return false;
    }

    ai_input  = ai_network_inputs_get(network_handle, NULL);
    ai_output = ai_network_outputs_get(network_handle, NULL);

    if (ai_input == NULL || ai_output == NULL) {
        uart_print("ERROR: AI buffers null\r\n");
        return false;
    }

    init_done = 1;
    uart_print("AI Init OK\r\n");
    return true;
}

bool ModelManager_RunInference(float temp, float cpu)
{
    (void)temp;
    (void)cpu;

    if (!init_done || network_handle == AI_HANDLE_NULL)
        return false;

    return true;
}

float ModelManager_GetOutput(uint8_t index)
{
    (void)index;
    return 0.0f;
}

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