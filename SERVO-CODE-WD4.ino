#include <Servo.h>

// Define the servo pin
const int servoPin = 7; //previously 10

// Create a Servo object
Servo myServo;

void setup() {
  // Attach the servo to the pin
  myServo.attach(servoPin);
}

void loop() {
  // Example: Sweep the servo from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) {
    myServo.write(pos); // Set the servo position
    delay(15); // Wait for the servo to reach the position
  }

  // Sweep the servo from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) {
    myServo.write(pos); // Set the servo position
    delay(15); // Wait for the servo to reach the position
  }
}
