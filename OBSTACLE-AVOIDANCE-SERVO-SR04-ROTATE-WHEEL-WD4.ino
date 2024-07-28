#include <Servo.h>

// Define pins
const int servoPin = 7;
const int trigPin = 13;
const int echoPin = 12;
const int ENA = 10;
const int ENB = 5;
const int IN1 = 9;
const int IN4 = 6;

// Create a Servo object
Servo myServo;

// Define variables for duration and distance
long duration;
int distance;
int maxDistance;
int maxAngle;

// Define motor speed (0-255)
const int motorSpeed = 100; // Adjust this value to control wheel speed

void setup() {
  // Servo and ultrasonic sensor setup
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Initialize serial communication
  Serial.begin(9600);

  // Start moving forward immediately
  moveForward();
}

void loop() {
  // Measure distance
  measureDistance();
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Check for obstacles
  if (distance < 20) {
    // Stop and find the best direction
    stopWheels();
    findBestDirection();
    // Turn to the best direction
    turn(maxAngle);
    // Resume forward motion
    moveForward();
  }
  
  delay(50);
}

void measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void findBestDirection() {
  maxDistance = 0;
  maxAngle = 0;
  
  for (int angle = 0; angle <= 180; angle += 10) {
    myServo.write(angle);
    delay(100); // Allow servo to reach position
    measureDistance();
    
    if (distance > maxDistance) {
      maxDistance = distance;
      maxAngle = angle;
    }
    
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(", Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  Serial.print("Best angle: ");
  Serial.print(maxAngle);
  Serial.print(", Max distance: ");
  Serial.print(maxDistance);
  Serial.println(" cm");
}

void moveForward() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
}

void stopWheels() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
}

void turn(int angle) {
  stopWheels();
  
  if (angle < 90) {
    // Turn left
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, HIGH);
  } else if (angle > 90) {
    // Turn right
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN4, LOW);
  }
  
  // Adjust this delay based on your robot's turning speed
  delay(map(abs(angle - 90), 0, 90, 0, 1000));
  
  stopWheels();
}