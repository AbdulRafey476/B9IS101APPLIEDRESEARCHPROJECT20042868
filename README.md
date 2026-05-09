# STM32F407 Hardware-Adaptive TinyML Inference System

**Student Name:** Abdul Rafey  
**Student ID:** 20042868  
**Programme:** MSc in Computing (Data Analytics/FinTech/Cloud Computing)  
**Institution:** Dublin Business School  
**Year:** 2026  

## Project Overview

This project implements a hardware-adaptive TinyML inference system on an STM32F407 microcontroller using X-CUBE-AI. The system collects real board telemetry, including temperature, voltage, and CPU load, and uses this runtime information to support adaptive inference-mode selection.

The final AI model uses two input features: temperature and CPU load. The output is one of three inference modes:

- STANDARD_INT8
- PRUNED_VARIANT
- MIXED_PRECISION

The firmware combines AI prediction with a rule-based fallback system. If the AI confidence is high, the AI decision is used. If confidence is below the threshold, the rule-based decision is used instead.

## Artefact Description

The artefact is a complete STM32F407 firmware-based prototype. It includes:

- STM32CubeIDE project source code
- X-CUBE-AI generated inference files
- Hardware profiling module
- Adaptation engine
- Model manager
- Trained AI model files
- Dataset copy
- Training files
- UART output evidence
- Project screenshots

## Folder Structure


20042868_STM32F407_Hardware_Adaptive_TinyML/
│
├── Artefact/
│   ├── Project_Code/
│   │   └── TINY_ML/
│   │
│   ├── Ai_Models/
│   │   ├── model.tflite
│   │   └── model.keras
│   │
│   ├── Training_Files/
│   │   ├── data_training.csv
│   │   └── training notebook / training command file
│   │
│   └── Evidence/
│       ├── UART output screenshots
│       ├── Google Colab training screenshot
│       └── STM32CubeIDE project screenshots
│
├── Report/
│   └── 20042868_STM32F407_Hardware_Adaptive_TinyML_Report.pdf
│
├── Presentation/
│   └── 20042868_STM32F407_Hardware_Adaptive_TinyML_Presentation.pptx
│
└── README.md


## Main Source Files

The main firmware implementation is located in:


Artefact/Project_Code/TINY_ML/Core/Src/


Important files include:


main.c
hardware_profile.c
adaptation_engine.c
model_manager_xcubeai.c


Important header files include:


hardware_profile.h
adaptation_engine.h
model_manager.h


## Runtime Behaviour

At runtime, the firmware performs the following process:

1. Initializes STM32 HAL peripherals.
2. Initializes the hardware profiler.
3. Initializes the adaptation engine.
4. Initializes the X-CUBE-AI model.
5. Reads board telemetry.
6. Runs AI inference using temperature and CPU load.
7. Compares AI prediction with rule-based decision.
8. Selects the final decision using confidence-gated fusion.
9. Prints the output through UART.

## Final UART Output Fields

The firmware prints the following fields:


Temperature
Voltage
CPU Load
AI Prediction
Rule Decision
Final Decided Mode
Decision Source

Example output:

[HW] T=60.88C | V=3.00V | CPU=44.56% | AI=STANDARD_INT8(1.000) | Rule=STANDARD_INT8 | Decided=STANDARD_INT8 | Src=AI
[HW] T=60.94C | V=3.00V | CPU=51.13% | AI=PRUNED_VARIANT(0.970) | Rule=PRUNED_VARIANT | Decided=PRUNED_VARIANT | Src=AI
[HW] T=60.87C | V=3.00V | CPU=59.68% | AI=MIXED_PRECISION(0.581) | Rule=PRUNED_VARIANT | Decided=PRUNED_VARIANT | Src=RULE


## AI Model Details

The model was trained using Google Colab and TensorFlow.

Model inputs:

Temperature
CPU Load

Model output classes:


0 = STANDARD_INT8
1 = PRUNED_VARIANT
2 = MIXED_PRECISION

Training details:

Input shape: (2,)
Hidden layer: Dense 16 ReLU
Output layer: Dense 3 Softmax
Optimizer: Adam
Loss: Sparse categorical crossentropy
Train/test split: 80/20 stratified
EarlyStopping patience: 10
Held-out accuracy: 83.2%

Normalisation constants:

TEMP_MEAN = 62.7824
TEMP_STD  = 1.8214
CPU_MEAN  = 53.4945
CPU_STD   = 8.0185

## Deployment Notes

The final deployment uses:

X-CUBE-AI 10.2.0
STM32CubeIDE
STM32 HAL drivers
STM32F407 / STM32F407VGTX
ARM Cortex-M4 FPU

TensorFlow Lite Micro was tested earlier during development, but the final working implementation uses X-CUBE-AI because the TFLM version produced zero output values and tensor pointer issues.

The STM32CubeIDE project was configured to use hard floating-point ABI for Cortex-M4 FPU support.

## How to Open the Project

1. Open STM32CubeIDE.
2. Select the workspace.
3. Go to:

File > Import > Existing Projects into Workspace

4. Select the project folder:


Artefact/Project_Code/


5. Build the project.
6. Flash the board using ST-LINK.
7. Open PuTTY or another serial monitor.
8. Observe UART output.


## Submission Contents

This submission includes:

* Final report PDF
* Final presentation PPTX
* Complete STM32CubeIDE project source code
* Dataset copy
* Trained model files
* Training files
* UART output evidence
* STM32CubeIDE screenshots
* Google Colab training screenshot

## Important Note

This project is not based on a public human activity recognition dataset. The dataset was collected from real STM32F407 board telemetry. The final artefact demonstrates a hardware-adaptive TinyML inference system using live board-state information.