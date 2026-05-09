#include "hardware_profile.h"
#include "main.h"

extern ADC_HandleTypeDef hadc1;

static HardwareState state;

static float movingAverage(float previous, float current, float alpha)
{
    return (alpha * current) + ((1.0f - alpha) * previous);
}

static uint32_t readAdcRaw(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

    uint32_t raw = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);

    return raw;
}

static float readTemperatureSensor(void)
{
    uint32_t raw = readAdcRaw(ADC_CHANNEL_TEMPSENSOR);

    float v_sense = ((float)raw * 3.3f) / 4095.0f;

    float temperature =
        ((v_sense - 0.76f) / 0.0025f) + 25.0f;

    return temperature;
}

static float readVcc(void)
{
    uint32_t raw_vref = readAdcRaw(ADC_CHANNEL_VREFINT);

    if (raw_vref == 0)
        return 0.0f;

    float vcc = (1.21f * 4095.0f) / (float)raw_vref;

    return vcc;
}

static float readCpuLoad(void)
{
    static uint32_t last_tick = 0;
    static float fake_load = 10.0f;

    uint32_t now = HAL_GetTick();

    if ((now - last_tick) >= 1000)
    {
        last_tick = now;

        fake_load += 7.0f;

        if (fake_load > 95.0f)
            fake_load = 15.0f;
    }

    return fake_load;
}

void HardwareProfiler_Init(void)
{
    state.temperature_c = 25.0f;
    state.vcc_volts = 3.30f;
    state.cpu_load_percent = 10.0f;
}

void HardwareProfiler_Sample(void)
{
    float temp = readTemperatureSensor();
    float vcc = readVcc();
    float cpu = readCpuLoad();

    state.temperature_c =
        movingAverage(state.temperature_c, temp, 0.2f);

    state.vcc_volts =
        movingAverage(state.vcc_volts, vcc, 0.2f);

    state.cpu_load_percent =
        movingAverage(state.cpu_load_percent, cpu, 0.2f);
}

HardwareState HardwareProfiler_GetState(void)
{
    return state;
}