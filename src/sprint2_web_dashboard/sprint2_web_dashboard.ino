#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

const char* ssid = "IdaHotspot";
const char* password = "wxil0840";

WebServer server(80);
Adafruit_AHTX0 aht;

float temperatureF = 0.0;
float humidityRH = 0.0;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Mold Risk Monitor</title>";
  html += "</head><body>";
  html += "<h1>Mold Risk Monitor</h1>";
  html += "<p><strong>Temperature:</strong> " + String(temperatureF, 2) + " &deg;F</p>";
  html += "<p><strong>Humidity:</strong> " + String(humidityRH, 2) + " %</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin();

  if (!aht.begin()) {
    Serial.println("Failed to find AHT10 sensor!");
    while (1) delay(10);
  }

  Serial.println("AHT10 detected successfully!");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  temperatureF = (temp.temperature * 9.0 / 5.0) + 32.0;
  humidityRH = humidity.relative_humidity;

  server.handleClient();

  delay(2000);
}
