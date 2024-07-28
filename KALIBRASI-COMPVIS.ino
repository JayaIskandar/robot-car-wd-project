#include <Servo.h>

Servo myServo;  // Create a servo object to control a servo

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 bits per second
  myServo.attach(7);     // Attach the servo to pin 4  //7 on robotics //5 on compvis
}

void loop() {
  int angle = 90;
  myServo.write(angle);  // Rotate to 90 degrees
  Serial.print("Current angle: ");
  Serial.println(angle);
  delay(1000);           // Wait for 1 second

  // angle = 180;
  // myServo.write(angle);  // Rotate to 180 degrees
  // Serial.print("Current angle: ");
  // Serial.println(angle);
  // delay(1000);           // Wait for 1 second

  // angle = 0;
  // myServo.write(angle);  // Rotate back to 0 degrees
  // Serial.print("Current angle: ");
  // Serial.println(angle);
  // delay(1000);           // Wait for 1 second
}
