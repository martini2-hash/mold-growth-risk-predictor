#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

const char* ssid = "IdaHotspot";
const char* password = "tempPw26";

WebServer server(80);
Adafruit_AHTX0 aht;

float temperatureF = 0.0;
float humidityRH = 0.0;

const int MAX_READINGS = 10;
float tempHistory[MAX_READINGS] = {0};
float humidityHistory[MAX_READINGS] = {0};
int readingCount = 0;

String trend = "Stable";
unsigned long lastUpdate = 0;

void handleRoot() {
  String risk;
  String color;
  String message;

  if (humidityRH < 60) {
    risk = "LOW";
    color = "#4ADE80"; // soft green
    message = "Environment is currently in a low-risk range.";
  } else if (humidityRH < 70) {
    risk = "MODERATE";
    color = "#FACC15"; // yellow
    message = "Humidity is increasing and should be monitored.";
  } else {
    risk = "HIGH";
    color = "#F87171"; // red
    message = "High humidity may support mold growth over time.";
  }

  unsigned long seconds = lastUpdate / 1000;

  String humidityData = "[";
  for (int i = MAX_READINGS - readingCount; i < MAX_READINGS; i++) {
    humidityData += String(humidityHistory[i], 1);
    if (i < MAX_READINGS - 1) humidityData += ",";
  }
  humidityData += "]";

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Mold Risk Monitor</title>";

  // 🎨 STYLE
  html += "<style>";
  html += "body { font-family: Arial; margin: 0; padding: 20px;";
  html += "background: #0B132B; color: white; }";

  html += ".card { background: #1C2541; padding: 25px;";
  html += "margin: auto; width: 900px; border-radius: 15px;";
  html += "box-shadow: 0 10px 30px rgba(0,0,0,0.4); }";

  html += ".container { display: flex; justify-content: space-between; align-items: flex-start; }";

  html += ".left { width: 45%; text-align: left; }";
  html += ".right { width: 50%; text-align: center; }";

  html += "h1 { text-align: center; }";

  html += ".value { font-size: 20px; margin: 8px 0; }";
  html += ".message { font-size: 14px; color: #cbd5e1; margin-top: 10px; }";
  html += ".trend { margin-top: 10px; font-size: 16px; }";

  html += ".history { margin-top: 15px; font-size: 13px; }";

  html += "canvas { background: white; border-radius: 10px; }";

  html += "</style>";
  html += "</head><body>";

  html += "<div class='card'>";
  html += "<h1>Mold Risk Monitor</h1>";

  html += "<div class='container'>";

  // LEFT SIDE
  html += "<div class='left'>";
  html += "<div class='value'><strong>Temperature:</strong> " + String(temperatureF, 2) + " °F</div>";
  html += "<div class='value'><strong>Humidity:</strong> " + String(humidityRH, 2) + " %</div>";
  html += "<div class='value'><strong>Mold Risk:</strong> <span style='color:" + color + ";'>" + risk + "</span></div>";
  html += "<div class='message'>" + message + "</div>";
  html += "<div class='trend'><strong>Trend:</strong> " + trend + "</div>";
  html += "<div class='message'><em>Last updated: " + String(seconds) + " sec</em></div>";

  html += "<div class='history'><strong>Recent Readings:</strong><ul>";
  for (int i = MAX_READINGS - readingCount; i < MAX_READINGS; i++) {
    html += "<li>" + String(humidityHistory[i], 1) + "%</li>";
  }
  html += "</ul></div>";
  html += "</div>";

  // RIGHT SIDE (GRAPH)
  html += "<div class='right'>";
  html += "<h3>Humidity Trend</h3>";
  html += "<canvas id='chart' width='400' height='220'></canvas>";
  html += "</div>";

  html += "</div>"; // container

  // GRAPH SCRIPT
  html += "<script>";
  html += "const data = " + humidityData + ";";
  html += "const c = document.getElementById('chart');";
  html += "const ctx = c.getContext('2d');";

  html += "ctx.beginPath(); ctx.moveTo(40,10); ctx.lineTo(40,200); ctx.lineTo(380,200); ctx.stroke();";

  html += "if(data.length > 1){";
  html += "let min=Math.min(...data)-1;";
  html += "let max=Math.max(...data)+1;";
  html += "ctx.beginPath();";

  html += "for(let i=0;i<data.length;i++){";
  html += "let x=40+i*(320/(data.length-1));";
  html += "let y=200-((data[i]-min)/(max-min))*180;";
  html += "if(i===0)ctx.moveTo(x,y); else ctx.lineTo(x,y);";
  html += "ctx.fillStyle='#3A506B'; ctx.fillRect(x-2,y-2,4,4);";
  html += "}";

  html += "ctx.strokeStyle='#3A506B'; ctx.lineWidth=2; ctx.stroke();";
  html += "}";

  html += "</script>";

  html += "</div></body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin();

  if (!aht.begin()) {
    Serial.println("Sensor not found!");
    while (1);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  temperatureF = (temp.temperature * 9.0 / 5.0) + 32.0;
  humidityRH = humidity.relative_humidity;
  lastUpdate = millis();

  for (int i = 0; i < MAX_READINGS - 1; i++) {
    tempHistory[i] = tempHistory[i + 1];
    humidityHistory[i] = humidityHistory[i + 1];
  }

  tempHistory[MAX_READINGS - 1] = temperatureF;
  humidityHistory[MAX_READINGS - 1] = humidityRH;

  if (readingCount < MAX_READINGS) readingCount++;

  if (readingCount >= 2) {
    float prev = humidityHistory[MAX_READINGS - 2];
    float curr = humidityRH;

    if (curr > prev + 0.2) trend = "Rising";
    else if (curr < prev - 0.2) trend = "Falling";
    else trend = "Stable";
  }

  server.handleClient();
  delay(2000);
}