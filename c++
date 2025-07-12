#include <NewPing.h>
#include <AFMotor.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 100

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motorLeft(1);  // Connect to Motor #1
AF_DCMotor motorRight(2); // Connect to Motor #2

void setup() {
  Serial.begin(9600);
  motorLeft.setSpeed(200); // Adjust speed (0–255)
  motorRight.setSpeed(200);
}

void loop() {
  int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance < 15) {
    // 🛑 Obstacle too close — react fast
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
    delay(300);

    motorLeft.run(FORWARD);
    motorRight.run(RELEASE); // Turn quickly
    delay(400);
  } else {
    // ✅ Safe to go forward
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
  }

  delay(50); // Keep loop snappy
}
