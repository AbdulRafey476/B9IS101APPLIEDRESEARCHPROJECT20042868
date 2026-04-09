# Hardware-Adaptive TinyML Runtime

This project bundle was prepared from your dissertation topic:

**Hardware-Level Adaptive Machine Learning for Embedded and IoT Systems**

## What is included
- **Hardware profiling module** for temperature, Vcc, and CPU load
- **Adaptation engine** with threshold + hysteresis logic
- **Model manager** for runtime variant switching
- **UART logger** for experiment data collection
- **Meeting update notes** for presenting progress

## Important note
This is a **project-aligned starter implementation**, not a verified production firmware.
You should present it as:
- prototype code
- framework skeleton
- initial embedded implementation draft

## Suggested talking points for your meeting
1. The runtime monitors:
   - chip temperature
   - supply voltage
   - CPU load
2. Based on hardware stress, it switches between:
   - Standard INT8
   - Pruned model
   - Mixed-precision model
3. The goal is:
   - better accuracy stability under heat
   - better energy efficiency under voltage sag
   - negligible overhead

## Next steps
- connect ADC and DWT register reads in STM32CubeIDE
- replace placeholder model arrays with real `.tflite` C arrays
- integrate with TensorFlow Lite Micro interpreter
- stream runtime metrics through UART for experiment logging
