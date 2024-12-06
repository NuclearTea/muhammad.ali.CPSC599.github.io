#include <Servo.h>

#define DELAY_DOWN_MS 10

Servo servo1;
Servo servo2;

const uint8_t initial_angle = 60;

const uint8_t max_angle = initial_angle + 120;
const uint8_t min_angle = initial_angle;

uint8_t current_rep = 1;  // Start on rep 1
uint8_t current_set = 1;  // Start on set 1
uint8_t total_sets = 0;   // Total number of sets
uint8_t reps[10];         // Array to store reps per set (max 10 sets)
uint8_t rpe[10];          // Array to store RPE per set (max 10 sets)

bool run = false;  // Flag to start the workout

void setup() {
  servo1.attach(8);
  servo2.attach(9);
  resetServos();

  Serial.begin(9600);  // Initialize serial communication
  Serial.println("Waiting for input: 1st byte = number of sets, then reps, then RPE...");
}

void loop() {
  if (!run) {
    receiveData();  // Receive data via UART
    return;
  }

  if (current_set > total_sets) {
    run = false;
    resetServos();
    servo1.detach();
    servo2.detach();
    Serial.println("Workout complete!");
    return;
  }

  // Calculate delay for servo movement
  const uint8_t delay_up_ms = mapDelay(current_rep, reps[current_set - 1], rpe[current_set - 1]);

  rotateServo(max_angle, min_angle, DELAY_DOWN_MS, delay_up_ms);
  current_rep++;

  if (current_rep > reps[current_set - 1]) {
    // Increment set
    current_set++;
    Serial.println("Resting till next set...");
    resetServos();
    delay(5000);
    current_rep = 1;
  }

  Serial.println("Current Set: " + String(current_set));
  Serial.println("Current Rep: " + String(current_rep));
}

// Function to receive the number of sets, reps, and RPE via UART
void receiveData() {
  if (Serial.available() < 1) return;  // Wait for at least the first byte

  total_sets = Serial.read();  // First byte: total sets

  if (total_sets < 1 || total_sets > 10) {
    Serial.println("Invalid number of sets. Must be between 1 and 10.");
    return;
  }

  // Wait for enough data: reps + RPE
  if (Serial.available() < 2 * total_sets) return;

  // Read reps for each set
  for (uint8_t i = 0; i < total_sets; i++) {
    reps[i] = Serial.read();
    if (reps[i] < 1) {
      Serial.println("Invalid reps value. Must be at least 1.");
      return;
    }
  }

  // Read RPE for each set
  for (uint8_t i = 0; i < total_sets; i++) {
    rpe[i] = Serial.read();
    if (rpe[i] < 1 || rpe[i] > 10) {
      Serial.println("Invalid RPE value. Must be between 1 and 10.");
      return;
    }
  }

  run = true;

  Serial.println("Data received:");
  Serial.println("Total Sets: " + String(total_sets));
  for (uint8_t i = 0; i < total_sets; i++) {
    Serial.println("Set " + String(i + 1) + ": Reps = " + String(reps[i]) + ", RPE = " + String(rpe[i]));
  }
}

void rotateServo(const uint8_t max_angle, const uint8_t min_angle, const uint8_t delay_down, const uint8_t delay_up) {
  uint8_t angle = 0;

  // Down movement
  for (angle = min_angle; angle < max_angle; angle++) {
    servo1.write(angle);
    servo2.write(180 - angle);
    delay(delay_down);
  }

  // Up movement
  for (angle = max_angle; angle > min_angle; angle--) {
    servo1.write(angle);
    servo2.write(180 - angle);
    delay(delay_up);
  }
}

// Function to map delay based on current rep, total reps, and RPE
uint8_t mapDelay(uint8_t current_rep, uint8_t total_reps, uint8_t rpe) {
  // Calculate a delay that increases with RPE and current rep proportionally
  float factor = 1.0 + ((float)current_rep / total_reps) * ((float)rpe / 10.0);
  return 30 * factor;
}

void resetServos() {
  servo1.write(180 - min_angle);
  servo2.write(min_angle);
}
