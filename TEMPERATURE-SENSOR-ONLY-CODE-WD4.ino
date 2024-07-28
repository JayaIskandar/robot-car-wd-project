#include <DHT.h>

#define DHTPIN 4     // Pin connected to the DATA pin of DHT11
#define DHTTYPE DHT11 // Define the type of sensor

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the DHT sensor
  dht.begin();
  
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

  // Print the temperature to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" °C");

  // Add a delay to simulate sampling time
  delay(1000);
}
