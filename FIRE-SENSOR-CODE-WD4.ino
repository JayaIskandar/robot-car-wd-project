// Define fire sensor pins
const int fireSensorPinA0 = A0;
const int fireSensorPinD11 = 11;

void setup() {
  // Set the fire sensor pins as input
  pinMode(fireSensorPinA0, INPUT);
  pinMode(fireSensorPinD11, INPUT);

  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  // Read the fire sensor values
  int fireDetectedA0 = digitalRead(fireSensorPinA0);
  int fireDetectedD11 = digitalRead(fireSensorPinD11);
  
  // Print the fire sensor status to the Serial Monitor for A0
  if (fireDetectedA0 == HIGH) {
    Serial.println("Fire detected on A0!");
  } else {
    Serial.println("No fire detected on A0.");
  }
  
  // Print the fire sensor status to the Serial Monitor for D11
  if (fireDetectedD11 == HIGH) {
    Serial.println("Fire detected on D11!");
  } else {
    Serial.println("No fire detected on D11.");
  }
  
  // Delay before taking the next measurement
  delay(500);
}
