// Define pins
const int INA = 2; // Control pin for motor
const int INB = 4; // Control pin for motor

void setup() {
  // Set the control pins as output
  pinMode(INA, OUTPUT);
  pinMode(INB, OUTPUT);

  // Initialize motor in a stopped state
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
}

void loop() {
  // Example: run the motor forward
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  delay(2000); // Run motor for 2 seconds

  // Stop the motor
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);

  delay(2000); // Stop for 2 seconds

  // Example: run the motor backward
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  delay(2000); // Run motor for 2 seconds

  // Stop the motor
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);

  delay(2000); // Stop for 2 seconds
}
