// Define pins for motor control
const int INA = 2; // Control pin for motor
const int INB = 4; // Control pin for motor

// Define fire sensor pins
const int fireSensorPinA0 = A0;
const int fireSensorPinD11 = 11;

void setup() {
  // Set the motor control pins as output
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  // Set the fire sensor pins as input
  pinMode(fireSensorPinA0, INPUT);
  pinMode(fireSensorPinD11, INPUT);

  // Initialize motor in a stopped state
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);

  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  // Read the fire sensor values
  int fireDetectedA0 = digitalRead(fireSensorPinA0);
  int fireDetectedD11 = digitalRead(fireSensorPinD11);

  // Check fire sensor status and print to the Serial Monitor
  if (fireDetectedA0 == HIGH) {
    Serial.println("Fire detected on A0!");
    // Turn on the fan
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
  } else {
    Serial.println("No fire detected on A0.");
    // Stop the fan
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
  }

  if (fireDetectedD11 == HIGH) {
    Serial.println("Fire detected on D11!");
    // Turn on the fan
    digitalWrite(INA, LOW);
    digitalWrite(INB, LOW);
  } else {
    Serial.println("No fire detected on D11.");
    // Stop the fan
    digitalWrite(INA, HIGH);
    digitalWrite(INB, LOW);
  }
  
  // Delay before taking the next measurement
  delay(500);
}
