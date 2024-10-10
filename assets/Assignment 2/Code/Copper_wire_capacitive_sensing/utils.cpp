#include "utils.h"

// helper function to print to serial
uint8_t printToSerial(String str) {
  Serial.println(str + "\n\r");
  return 1;
}
