#include <Wire.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
unsigned long startTime;

void setup() {
  Serial.begin(115200);
  delay(1000);
  startTime = millis();

  Serial.println("AHT10 Test Starting...");

  Wire.begin();  // Use default I2C pins (D4 = SDA, D5 = SCL)

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10 sensor!");
    while (1) delay(10);
  }

  Serial.println("AHT10 detected successfully!");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  float tempF = (temp.temperature * 9.0 / 5.0) + 32.0;
  unsigned long seconds = (millis() - startTime) / 1000;

  Serial.print("Time: ");
  Serial.print(seconds);
  Serial.print("s | Temperature: ");
  Serial.print(tempF);
  Serial.print(" °F  |  ");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(2000);
}