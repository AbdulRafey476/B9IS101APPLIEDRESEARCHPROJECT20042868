/*
 * model_manager_xcubeai.c
 * X-CUBE-AI 10.2.0 inference — STM32F407
 * Model: Dense(2→16→3) float32
 * Classes: STANDARD_INT8=0, PRUNED_VARIANT=1, MIXED_PRECISION=2
 */

#include "model_manager.h"
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "network.h"
#include "network_data.h"

/* ------------------------------------------------------------------ */
#define TEMP_MEAN   62.7824f
#define TEMP_STD     1.8214f
#define CPU_MEAN    53.4945f
#define CPU_STD      8.0185f

extern UART_HandleTypeDef huart2;

static void uart_print(const char* msg)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

/* ------------------------------------------------------------------ */
AI_ALIGNED(4) static ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];
static const ai_handle act_ptrs[1] = { (ai_handle)activations };

static ai_handle  network_handle = AI_HANDLE_NULL;
static float      last_output[3] = {0.0f, 0.0f, 0.0f};
static int        init_done      = 0;

static ai_buffer *ai_input  = NULL;
static ai_buffer *ai_output = NULL;

/* ------------------------------------------------------------------ */
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

/* ------------------------------------------------------------------ */
bool ModelManager_RunInference(float temp, float cpu)
{
    if (!init_done || network_handle == AI_HANDLE_NULL)
        return false;

    float input_data[AI_NETWORK_IN_1_SIZE];
    input_data[0] = (temp - TEMP_MEAN) / TEMP_STD;
    input_data[1] = (cpu  - CPU_MEAN)  / CPU_STD;

    float output_data[AI_NETWORK_OUT_1_SIZE];

    ai_input[0].data  = AI_HANDLE_PTR(input_data);
    ai_output[0].data = AI_HANDLE_PTR(output_data);

    ai_i32 n = ai_network_run(network_handle, ai_input, ai_output);

    if (n != 1) return false;

    last_output[0] = output_data[0];
    last_output[1] = output_data[1];
    last_output[2] = output_data[2];

    return true;
}

/* ------------------------------------------------------------------ */
float ModelManager_GetOutput(uint8_t index)
{
    if (index > 2) return 0.0f;
    return last_output[index];
}

/* ------------------------------------------------------------------ */
void ModelManager_Init(void) {}
void ModelManager_SwitchTo(ModelVariant variant) { (void)variant; }
ModelDescriptor ModelManager_CurrentModel(void)
{
    ModelDescriptor d = {0};
    return d;
}