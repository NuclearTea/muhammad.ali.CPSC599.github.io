#ifndef UTILS_H
#define UTILS_H
#include "Arduino.h"
#include "CapacitiveSensor.h"
#include "CapacitiveSensorCalibration.h"

// Type for calibration function
typedef void (*calibrationFunc)(CapacitiveSensor *, CapacitiveSensorCalibration *);

uint8_t printToSerial(String str);

#endif // UTILS_H