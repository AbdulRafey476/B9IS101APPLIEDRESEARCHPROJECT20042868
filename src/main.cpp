#include "hardware_profile.h"
#include "adaptation_engine.h"
#include "model_manager.h"
#include <cstdio>

// Demo main loop for STM32 / TFLite Micro style runtime.
// Replace printf with UART transmit or SWV logging in your target project.

int main() {
    HardwareProfiler profiler;
    AdaptationEngine engine;
    ModelManager models;

    profiler.init();
    models.init();

    while (true) {
        profiler.sample();
        HardwareState hw = profiler.getState();

        ModelVariant selected = engine.decide(hw);
        models.switchTo(selected);

        // Placeholder for TFLite Micro inference call
        // interpreter->Invoke();

        std::printf(
            "Temp=%.2fC, Vcc=%.2fV, Load=%.2f%%, Model=%s\n",
            hw.temperature_c,
            hw.vcc_volts,
            hw.cpu_load_percent,
            engine.toString(selected)
        );

        // Add delay / scheduler hook here
        break; // Remove for real embedded loop
    }

    return 0;
}
