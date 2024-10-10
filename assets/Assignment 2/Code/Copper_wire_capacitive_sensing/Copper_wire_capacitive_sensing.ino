#include <CapacitiveSensor.h>
#include <stdint.h>

#include "utils.h"
#include "MidiAPI.h"
#include "CapacitiveSensorCalibration.h"


// These are mapped to digital pins
#define FIRST_COPPER_WIRE_PIN 2
#define VOLUME_COPPER_WIRE_PIN 3
#define DELAY 10000 // This represents the amount of time for calibration

// CapacitiveSensor(<send pin>, <receive pin>)
CapacitiveSensor firstCapSensor = CapacitiveSensor(4, FIRST_COPPER_WIRE_PIN);
CapacitiveSensor volumeCapSensor = CapacitiveSensor(4, VOLUME_COPPER_WIRE_PIN);

CapacitiveSensorCalibration first_sensor = {
  .avg = 0,
  .maximum = 0,
  .minimum = 0,
  .note_playing = false
};

CapacitiveSensorCalibration volume_sensor = {
  .avg = 0,
  .maximum = 0,
  .minimum = 0,
  .note_playing = false
};

void setup() {
  Serial.begin(9600);
  first_sensor.avg = 0;
  volume_sensor.avg = 0;
  const uint32_t iterations = calibrate();
  first_sensor.avg /= iterations;
  volume_sensor.avg /= iterations;
}

void loop() {
  noteSensor(48, &firstCapSensor, &first_sensor);
  volumeSensor();
  // Add a small delay
  delay(5);
}

/// calibration function which just runs a while loop for DELAY seconds
/// the functions can be for anything and just need to be added to the calibrate_func_arr variable
uint32_t calibrate() {
  calibrationFunc calibrate_func_arr[] = { calibrateSensor };

  const int initial_time = millis();
  printToSerial("Calibrating Start");
  uint32_t i = 0;
  while ((millis() - initial_time) < DELAY) {
    for (auto func : calibrate_func_arr) {
      func(&firstCapSensor, &first_sensor);
      func(&volumeCapSensor, &volume_sensor);
    }
    i++;
  }
  printToSerial("Calibrating END");
  return i;
}

/// Meant to be run during the calibrate function
/// calculates maximum, average, and minimum readings for capacitive sensors
void calibrateSensor(CapacitiveSensor* capSensor, CapacitiveSensorCalibration* sensor_calibration) {
  long reading = capSensor->capacitiveSensor(30);
  sensor_calibration->avg += reading;
  if (reading > sensor_calibration->maximum) {
    sensor_calibration->maximum = reading;
  } else if (reading < sensor_calibration->minimum) {
    sensor_calibration->minimum = reading;
  }
}

void noteSensor(byte note, CapacitiveSensor* capSensor, CapacitiveSensorCalibration* sensor_calibration) {
  long firstSensorValue = capSensor->capacitiveSensor(30);
  // printToSerial(String(firstSensorValue));
  // printToSerial("NOTE AVG: " + String(note) + " " + String((int32_t)sensor_calibration->avg));
  // printToSerial("NOTE MAX: " + String(note) + " " + String(sensor_calibration->maximum));
  // printToSerial("NOTE MIN: " + String(note) + " " + String(sensor_calibration->minimum));


  const long signal_present = map(firstSensorValue, sensor_calibration->minimum, sensor_calibration->maximum, 0, 1);

  if (signal_present && !sensor_calibration->note_playing) {
    playNote(note, 127);
    sensor_calibration->note_playing = true;
  } else if (!signal_present && sensor_calibration->note_playing) {
    sensor_calibration->note_playing = false;
    turnOffNote(note, 127);
  }
}

void volumeSensor() {
  long volumeSensorValue = volumeCapSensor.capacitiveSensor(30);

  // printToSerial("Vol AVG: " + String((int32_t)volume_sensor.avg));
  // printToSerial("Vol MAX: " + String(volume_sensor.maximum));
  // printToSerial("Vol MIN: " + String(volume_sensor.minimum));

  const long mapped_vol = map(volumeSensorValue, volume_sensor.minimum, volume_sensor.avg, 127 / 2, 127);
  
  // can use the diff to change the way volume is mapped
  // const int32_t diff = volumeSensorValue - volume_sensor.avg;
  changeVolume(mapped_vol);
}
