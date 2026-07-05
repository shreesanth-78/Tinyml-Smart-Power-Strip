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

