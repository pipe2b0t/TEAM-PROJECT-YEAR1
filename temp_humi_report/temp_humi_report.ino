#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "P2B";        // Your WiFi SSID
const char* password = "pipe281148;"; // Your WiFi password
String scriptID = "https://script.google.com/macros/s/AKfycbxP7vZA5y8LULfQokyQikGzJJkbHY5ChYz_g1wSZh9D45EufL_8GDFNr8K8vYh1FCrh/exec";

#include "DHT.h"
#define DHTPIN 32   
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(115200);
  Serial.println(F("DHTxx test!"));

  dht.begin();
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
}
unsigned long previousT = 0;
const unsigned long Tsent = 300000;
void loop() {
  unsigned long currentT = millis();
 if(currentT - previousT >= Tsent){
   previousT = currentT;
   if (WiFi.status() == WL_CONNECTED) {
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        if (!isnan(temperature) && !isnan(humidity)) {
            HTTPClient http;
            String url = scriptID + "?temperature=" + String(temperature) + "&humidity=" + String(humidity);
            http.begin(url);
            int httpCode = http.GET();
            Serial.println(httpCode);
            if (httpCode > 0) {
                    Serial.println("Data Sent!");
                } else {
                    Serial.println("Failed to Send Data");
                }
            http.end();
        }
    }
    else {
                Serial.println("WiFi Disconnected, Reconnecting...");
                WiFi.begin(ssid, password);
            }
 }
}
