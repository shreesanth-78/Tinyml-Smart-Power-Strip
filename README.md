# TinyML Smart Power Strip: Appliance Identification & Energy Monitoring

## Overview
This repository contains the firmware, data processing scripts, and documentation for a TinyML-based intelligent power strip. The system autonomously identifies connected electrical appliances and continuously monitors their energy consumption, transmitting the processed data to a ThingSpeak IoT cloud platform. 

By executing a fully-connected dense neural network directly on a resource-constrained ESP8266 NodeMCU, this project demonstrates that intelligent non-intrusive load monitoring (NILM) can be achieved without relying on a central gateway, heavy edge devices, or cloud inference engines.

## Features
* **On-Device Machine Learning:** Int8-quantized TFLite Micro model deployed natively on an ESP8266.
* **Spectral Feature Extraction:** Computes a 128-point FFT locally to extract harmonic signatures from the AC current waveform.
* **Real-Time Energy Monitoring:** Computes RMS current and apparent power simultaneously with classification.
* **IoT Cloud Integration:** Uploads appliance ID, confidence scores, and power metrics to a ThingSpeak dashboard over Wi-Fi.
* **Frugal Resource Usage:** The inference pipeline executes in ~1 ms and consumes only 1.4 KB of RAM and 15.7 KB of Flash.

## System Architecture

```mermaid
flowchart LR
    A[Connected Appliance] -->|230V AC| B[Smart Extension Board]
    B -->|Live Wire Series| C[ACS712 Current Sensor]
    C -->|Analog Signal| D{ESP8266 NodeMCU}
    
    subgraph Edge Processing
    D --> E[Offset Calibration]
    E --> F[128-point FFT Extraction]
    F --> G[Dense NN Inference]
    G --> H[Energy Computation]
    end
    
    H -->|Wi-Fi HTTP GET| I[(ThingSpeak Dashboard)]

## Hardware Setup

Microcontroller: ESP8266 NodeMCU 1.0 (ESP-12E)

Current Sensor: ACS712-05B (185 mV/A sensitivity)

Physical Interface: Modified 4-socket Indian-type (BS 546) extension board

Data Collection Node: Arduino UNO (used strictly for stable 500 Hz offline data acquisition)

## Software & Toolchain
Edge Impulse Studio: For spectral DSP configuration, model training, and C++ library generation.

Arduino IDE / VS Code: For firmware compilation and deployment.

Python 3: For segmenting raw serial dumps into timestamped 200-sample windows.

ThingSpeak: For live IoT data visualization.

## Performance & Results
The model was trained to identify five specific load classes: No Load, Phone Charger, Laptop Charger, Pedestal Fan, and Electric Kettle.

Validation Accuracy: 91.0%

Real-world Performance: 100% recall on high-power loads (Fan, Kettle, Laptop) with confidence scores > 0.99.

Note: Occasional confusion exists between the idle 'No Load' state and a low-power phone charger due to the 10-bit ADC hardware limitation of the ESP8266.

## Future Scope
Upgrading to an external 16-bit ADC (e.g., ADS1115) to improve low-current feature resolution.

Expanding the appliance dataset.

Implementing HTTPS/TLS for secure IoT telemetry.