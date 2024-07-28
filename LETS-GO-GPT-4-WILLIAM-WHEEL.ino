#define ENA 10
#define ENB 5
#define IN1 9
//#define IN2 8
#define IN4 6

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENA, HIGH); // Enable the motor
  digitalWrite(ENB, HIGH); // Enable the motor
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN4, HIGH); // Ensure the motor runs in one direction
  delay(1000);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN4, LOW); // Stop the motor
  delay(1000);
}
