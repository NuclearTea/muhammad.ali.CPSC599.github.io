#include <Servo.h>

#define DELAY_DOWN_MS 10

Servo servo1;
Servo servo2;

const uint8_t initial_angle = 60;

const uint8_t max_angle = initial_angle + 120;
const uint8_t min_angle = initial_angle;

void setup() {
  servo1.attach(8);
  servo2.attach(9);

  resetServos();
}


bool run = true;
uint8_t current_rep = 1;  // start on rep 1
uint8_t current_set = 1;  // start on set 1

// each index corresponds the the respective set (+1)
const uint8_t reps[] = { 15, 12, 8 };
const uint8_t rpe[] = { 9, 9, 10 };

void loop() {
  if (run) {
    if (current_set > 4) {
      run = false;
      resetServos();
      servo1.detach();
      servo2.detach();
    }


    // how long it should take to move arms up
    const uint8_t delay_up_ms = mapDelay(current_rep, reps[current_set - 1], rpe[current_set - 1]);

    rotateServo(max_angle, min_angle, DELAY_DOWN_MS, delay_up_ms);
    current_rep++;
    
    
    if (current_rep >= reps[current_set - 1]) {
      // increment set
      current_set++;
      Serial.println("Resting till next set!");
      resetServos();
      delay(5000);
      current_rep = 1;
    }
    
    Serial.println("Current Set: " + String(current_set));
    Serial.println("Current Rep: " + String(current_rep));
  }
}

void rotateServo(const uint8_t max_angle, const uint8_t min_angle, const uint8_t delay_down, const uint8_t delay_up) {
  uint8_t angle = 0;

  // down
  for (angle = min_angle; angle < max_angle; angle++) {
    servo1.write(angle);
    servo2.write(180 - angle);
    delay(delay_down);
  }

  // up
  for (angle = max_angle; angle > min_angle; angle--) {
    servo1.write(angle);
    servo2.write(180 - angle);
    delay(delay_up);
  }
}

// from chatgpt
// Function to map delay based on current rep, total reps, and RPE
uint8_t mapDelay(uint8_t current_rep, uint8_t total_reps, uint8_t rpe) {
  // Calculate a delay that increases with RPE and current rep proportionally
  float factor = 1.0 + ((float)current_rep / total_reps) * (float(rpe) / 10.0);
  return 30 * factor;
}

void resetServos() {
  servo1.write(min_angle);
  servo2.write(min_angle);
}
