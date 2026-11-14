#include "VL53L0X.h"
#include "TCA9548.h"
#include "Wire.h"

TCA9548 MP(0x70);
const int o = 5;
VL53L0X sensors[o];
uint16_t distances[o];
int counter = 0;
int ver = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(100000); // 100 kHz I2C for reliable 50 Hz polling across all 5 channels

  if (!MP.begin()) {
    Serial.println("TCA9548 not found!");
    while (1);
  }
  for (uint8_t i = 0; i < o; i++) {
    MP.selectChannel(i);
    sensors[i].setTimeout(500);
    if (!sensors[i].init()) {
      Serial.print("Sensor failed on channel ");
      Serial.println(i);
      while (1);
    }
    sensors[i].setMeasurementTimingBudget(20000); // 20 ms timing budget (50 Hz)
    sensors[i].startContinuous();
  }
}

void loop() {
  for (uint8_t i = 0; i < o; i++) {
    MP.selectChannel(i);
    distances[i] = sensors[i].readRangeContinuousMillimeters();
  }
  Serial.println(distances[counter]);
  counter++;
  if (counter >= o) {
    counter = 0;
  }

  ver = (distances[0] + distances[1] + distances[2] + distances[3] + distances[4]) / 5;
}
