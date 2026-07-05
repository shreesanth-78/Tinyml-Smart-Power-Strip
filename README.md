# ⚡ TinyML Smart Power Strip: Appliance Identification & Energy Monitoring

![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![Hardware](https://img.shields.io/badge/Hardware-ESP8266-black?style=flat-square)
![License: MIT](https://img.shields.io/badge/License-MIT-green?style=flat-square)

## 📖 Overview
This repository contains the firmware, data processing scripts, and documentation for a TinyML-based intelligent power strip. The system autonomously identifies connected electrical appliances and continuously monitors their energy consumption, transmitting the processed data to a ThingSpeak IoT cloud platform. 

By executing a fully-connected dense neural network directly on a resource-constrained ESP8266 NodeMCU, this project demonstrates that intelligent non-intrusive load monitoring (NILM) can be achieved without relying on a central gateway, heavy edge devices, or cloud inference engines.

## ✨ Features
* **On-Device Machine Learning:** Int8-quantized TFLite Micro model deployed natively on an ESP8266.
* **Spectral Feature Extraction:** Computes a 128-point FFT locally to extract harmonic signatures from the AC current waveform.
* **Real-Time Energy Monitoring:** Computes RMS current and apparent power simultaneously with classification.
* **IoT Cloud Integration:** Uploads appliance ID, confidence scores, and power metrics to a ThingSpeak dashboard over Wi-Fi.
* **Frugal Resource Usage:** The inference pipeline executes in ~1 ms and consumes only 1.4 KB of RAM and 15.7 KB of Flash.

## 🏗️ System Architecture

![System Architecture](images/System%20Architecture.png)

## 🔌 Hardware Setup
* **Microcontroller:** ESP8266 NodeMCU 1.0 (ESP-12E) running at 80 MHz.
* **Current Sensor:** ACS712-05B isolated Hall-effect current transducer (185 mV/A sensitivity).
* **Physical Interface:** Modified 4-socket Indian-type (BS 546) extension board operating at 230 V AC, 50 Hz.
* **Data Collection Node:** Arduino UNO (used strictly for stable 500 Hz offline data acquisition due to its stable 10-bit ADC).

### Wiring Guide
The ACS712 module is placed in series with the live wire of the extension board. The analog output of the ACS712 is connected to the `A0` analog pin of the ESP8266. The sensor is powered via the microcontroller's 3.3V/5V rails.

## 📊 Dataset & Preprocessing
The model was trained to identify five specific load classes spanning 0 W to 1500 W:
1. **No Load** (0 W)
2. **Phone Charger** (~7.75 W)
3. **Laptop Charger** (65 W)
4. **Pedestal Fan** (120 W)
5. **Electric Kettle** (1500 W)

Data was collected at a physical acquisition rate of 500 Hz (2 ms inter-sample delay) using the Arduino UNO. Python scripts segmented this data into 200-sample non-overlapping windows and applied 1 ms timestamps, mapping the data to a 1000 Hz logical sampling rate. This dataset totals 75,000 samples per class (1,875 windows).

## 🧠 Model Architecture (Edge Impulse)
* **DSP Block:** Spectral Analysis with a 128-point FFT length, extracting 69 spectral features per window.
* **Neural Network:**
  * **Input layer:** 69 spectral features
  * **Hidden Layer 1:** 20 neurons (ReLU)
  * **Hidden Layer 2:** 10 neurons (ReLU)
  * **Output Layer:** 5 neurons (Softmax)
* **Training:** 50 epochs with auto-tuned Adam optimizer.

## 📈 Performance & Results
* **Validation Accuracy:** 91.0%
* **Real-world Performance:** 100% recall on high-power loads (Fan, Kettle, Laptop) with confidence scores > 0.99.
* **Known Limitations:** Occasional confusion exists between the idle 'No Load' state and a low-power phone charger due to the 10-bit ADC hardware limitation of the ESP8266 producing similar harmonic profiles at very low RMS currents (<50 mA).

## 🚀 Installation & Usage
1. Clone this repository: `git clone https://github.com/YOUR_USERNAME/tinyml-smart-power-strip.git`
2. Open the `firmware/deployment/deployment.ino` file in the Arduino IDE or VS Code.
3. Install the exported Edge Impulse library (`Smart_Appliance_Identification_inferencing.zip`) via **Sketch > Include Library > Add .ZIP Library**.
4. Update the Wi-Fi credentials (`ssid`, `password`) and your ThingSpeak `apiKey` in the code.
5. Flash to the ESP8266 NodeMCU.
6. Connect the hardware and open the Serial Monitor (115200 baud) to view real-time inference and upload status.

## 🔮 Future Scope
* Upgrading to an external 16-bit ADC (e.g., ADS1115) to improve low-current feature resolution.
* Expanding the appliance dataset.
* Implementing HTTPS/TLS for secure IoT telemetry.
* Exploring multi-appliance simultaneous load disaggregation on the edge device.

## 🎓 Authors & Citation
**Shree Santh B, Kirupashankar Chockkanathan, Padmacharan R, Prapanjan I, Abhishek S**  
*Amrita School of Artificial Intelligence, Coimbatore, Amrita Vishwa Vidyapeetham, India*

If you use this project or dataset, please refer to our corresponding conference paper.

## 📄 License
This project is licensed under the MIT License. See the `LICENSE` file for details.