#include <PID_v1.h>
#include <DHT.h>
#include <Servo.h>

// Temperature sensor pins and settings
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Fire sensor pins
const int fireSensorPinA0 = A0;
const int fireSensorPinD11 = 11;
const int INA = 2;
const int INB = 4;

// Obstacle avoidance pins
const int servoPin = 7;
const int trigPin = 13;
const int echoPin = 12;
const int ENA = 10;
const int ENB = 5;
const int IN1 = 9;
const int IN4 = 6;

// Create Servo object
Servo myServo;

// Variables for ultrasonic sensor
long duration;
int distance;
int maxDistance;
int maxAngle;
const int motorSpeed = 100;

// PID variables
double Setpoint, Input, Output;
// PID tuning parameters (adjust these as needed)
double Kp = 10, Ki = 0.1, Kd = 0.5;

// Create PID instance
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

void setup() {
  // Initialize DHT sensor
  dht.begin();
  
  // Set the motor control pins as output
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  // Set the fire sensor pins as input
  pinMode(fireSensorPinA0, INPUT);
  pinMode(fireSensorPinD11, INPUT);

  // Initialize motor in a stopped state
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);

  // Servo and ultrasonic sensor setup
  myServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(ENA, HIGH); // Enable the motor
  digitalWrite(ENB, HIGH); // Enable the motor

  // Initialize the PID controller
  Setpoint = 20; // Desired maximum temperature
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255); // Constrain the PID output to PWM range

  // Initialize Serial Monitor
  Serial.begin(9600);

  // Start moving forward immediately
  moveForward();

  // Ensure the motor runs in one direction
  digitalWrite(ENA, HIGH); // Enable the motor
  digitalWrite(ENB, HIGH); // Enable the motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
}

void loop() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH); // Ensure the motor runs in one direction
  delay(1000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW); // Stop the motor
  delay(1000);

  // Read and print temperature
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.println(" °C");
  }

  // PID control based on temperature
  Input = temperature;
  myPID.Compute();
  controlMotorsBasedOnTemperature();

  // Check fire sensors
  checkFireSensors();

  // Measure and handle distance for obstacle avoidance
  measureDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 50) {
    stopWheels();
    delay(3000); // Stop for 3 seconds to scan the area
    findBestDirection();
    moveBackward();
    delay(1000); // Move backward for 0.5 seconds
    stopWheels();
    turn(maxAngle);
    moveForward();
  }

  delay(100); // Reduced delay to keep the robot responsive
}

void controlMotorsBasedOnTemperature() {
  if (Input > 15) {
    // Move wheels with PID-controlled speed
    digitalWrite(ENA, Output);
    digitalWrite(ENB, Output);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN4, HIGH);
    
    Serial.print("Motors ON - Speed: ");
    Serial.println(Output);
  } else {
    // Stop all wheels
    digitalWrite(ENA, 0);
    digitalWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, LOW);
    
    Serial.println("Motors OFF - Temperature 15°C or below");
  }
  
  // Print PID values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(Input, 2);
  Serial.print(" °C\t");
  Serial.print("Setpoint: ");
  Serial.print(Setpoint, 2);
  Serial.print(" °C\t");
  Serial.print("PID Output: ");
  Serial.println(Output, 2);
}

void checkFireSensors() {
  int fireDetectedA0 = digitalRead(fireSensorPinA0);
  int fireDetectedD11 = digitalRead(fireSensorPinD11);

  if (fireDetectedA0 == HIGH) {
    Serial.println("Fire detected on A0!");
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
  } else {
    Serial.println("No fire detected on A0.");
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
  }

  if (fireDetectedD11 == HIGH) {
    Serial.println("Fire detected on D11!");
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
  } else {
    Serial.println("No fire detected on D11.");
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
  }
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
    delay(100);
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

  // Recalibrate back to 90 degrees
  myServo.write(90);
  Serial.println("Recalibrating servo to 90 degrees.");
  delay(1000); // Wait for 1 second to ensure servo reaches 90 degrees
}

void moveForward() {
  digitalWrite(ENA, motorSpeed);
  digitalWrite(ENB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH);
  //delay(3000);
}

void moveBackward() {
  digitalWrite(ENA, motorSpeed);
  digitalWrite(ENB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW);
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
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, HIGH);
  } else if (angle > 90) {
    digitalWrite(ENA, HIGH);
    digitalWrite(ENB, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN4, LOW);
  }
  delay(map(abs(angle - 90), 0, 90, 0, 1000));
  stopWheels();
}