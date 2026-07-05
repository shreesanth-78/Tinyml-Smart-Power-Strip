// ==============================================================================
// RECONSTRUCTED CODE
// Based on methodology described in Section II-B of the conference paper.
// Goal: Sample ACS712 analog output at 500 Hz and stream via Serial to PC.
// ==============================================================================

const int sensorPin = A0; // ACS712 analog output connected to A0
const unsigned long sampleIntervalMicros = 2000; // 2 ms = 2000 microseconds (500 Hz)

unsigned long previousMicros = 0;

void setup() {
  // Initialize serial communication at a high baud rate for fast data streaming
  Serial.begin(115200);
  
  // Wait for serial port to connect
  while (!Serial) {
    ; 
  }
}

void loop() {
  unsigned long currentMicros = micros();

  // Non-blocking delay to ensure exactly 500 Hz sampling rate
  if (currentMicros - previousMicros >= sampleIntervalMicros) {
    previousMicros = currentMicros;
    
    // Read the 10-bit ADC value (0-1023)
    int adcValue = analogRead(sensorPin);
    
    // Print the raw value to Serial
    Serial.println(adcValue);
  }
}