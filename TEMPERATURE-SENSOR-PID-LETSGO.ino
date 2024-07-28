#include <PID_v1.h>
#include <DHT.h>

#define DHTPIN 4 // Pin connected to the DATA pin of DHT11
#define DHTTYPE DHT11 // Define the type of sensor
#define ENA 10 // Motor A speed control
#define ENB 5 // Motor B speed control
#define IN1 9 // Motor A direction control
#define IN4 6 // Motor B direction control

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// PID variables
double Setpoint, Input, Output;
// PID tuning parameters (adjust these as needed)
double Kp = 10, Ki = 0.1, Kd = 0.5;

// Create PID instance
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, REVERSE);

void setup() {
  // Initialize the motor control pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the PID controller
  Setpoint = 20; // Desired maximum temperature
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255); // Constrain the PID output to PWM range

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read the temperature from the DHT11 sensor
  float temperature = dht.readTemperature();

  // Check if the reading is valid
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Input = temperature;

  // Compute the PID output
  myPID.Compute();

  // Determine motor control based on temperature
  if (temperature > 15) {
    // Move wheels with PID-controlled speed
    int motorSpeed = Output;
    digitalWrite(ENA, motorSpeed);
    digitalWrite(ENB, motorSpeed);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN4, HIGH);
    
    Serial.print("Motors ON - Speed: ");
    Serial.println(motorSpeed);
  } else {
    // Stop all wheels
    digitalWrite(ENA, 0);
    digitalWrite(ENB, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN4, LOW);
    
    Serial.println("Motors OFF - Temperature 15°C or below");
  }

  // Print the values to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(Input, 2);
  Serial.print(" °C\t");
  Serial.print("Setpoint: ");
  Serial.print(Setpoint, 2);
  Serial.print(" °C\t");
  Serial.print("PID Output: ");
  Serial.println(Output, 2);

  // Add a delay to simulate sampling time
  delay(1000);
}