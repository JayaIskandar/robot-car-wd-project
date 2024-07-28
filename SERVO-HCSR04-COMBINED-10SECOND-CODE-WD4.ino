#include <Servo.h>

// Define pins
const int servoPin = 7;
const int trigPin = 13;
const int echoPin = 12;

// Create a Servo object
Servo myServo;

// Define variables for duration and distance
long duration;
int distance;
unsigned long startTime;

void setup() {
  // Attach the servo to the pin
  myServo.attach(servoPin);
  
  // Set the trigger and echo pins as output and input, respectively
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Record the start time
  startTime = millis();
}

void loop() {
  // Check if 10 seconds have passed
  if (millis() - startTime < 5000) {
    // Measure distance
    measureDistance();
    
    // Print the distance to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Control servo based on distance
    controlServo();
    
    // Delay before taking the next measurement
    delay(500);
  } else {
    // After 10 seconds, set the servo to 90 degrees and stop
    myServo.write(90);
    Serial.println("Servo stopped at 90 degrees");
    while(1); // This will cause the program to stop here
  }
}

void measureDistance() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, and calculate the distance
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;
}

void controlServo() {
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