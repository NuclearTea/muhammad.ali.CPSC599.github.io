#ifndef CAPCITIVE_SENSOR_CALIBRATION
#define CAPCITIVE_SENSOR_CALIBRATION
#include <stdint.h>

struct CapacitiveSensorCalibration {
  int64_t avg;
  long maximum;
  long minimum;
  bool note_playing;
};

#endif  // CAPCITIVE_SENSOR_CALIBRATION