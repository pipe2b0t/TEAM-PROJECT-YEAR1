#include <HardwareSerial.h>

#define esp32_RX 16  // ESP32 RX pin connect with TX scanner
#define esp32_TX 17  // ESP32 TX pin connect with RX scanner
HardwareSerial scanner(2);  // Using UART2 TX2 RX2


#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "P2B";       
const char* password = "pipe281148;"; 
String scriptid = "https://script.google.com/macros/s/AKfycbwuutmpR3f7NVsasOKBvUi-ISVdE5vS8vu5a4VO4G0CHo6SSp1fiqCRa7V525hK8RS_/exec";

#include <Ultrasonic.h>
Ultrasonic ultrasonic(12, 13); // Trig 12 and Echo 13
int distance;
int fixdistance = 20;

void setup() {
    Serial.begin(115200);
    pinMode(32, OUTPUT); // relay pin 32
    scanner.begin(9600, SERIAL_8N1, esp32_RX, esp32_TX);

    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

}


unsigned long previous = 0;
const unsigned long waittime = 1000;


void loop() {
    unsigned long current = millis();
    String id;
    
   
    if ((current - previous) >= waittime){
      previous = current;
      distance = ultrasonic.read();
      Serial.print("Distance in CM: ");
      Serial.println(distance);
      if(distance < fixdistance){
          digitalWrite(32, 1);
          while (scanner.available()) {
          
          id = scanner.readStringUntil('\n');
          
          String toRemove = "T"; // Substring to remove
          // Remove all occurrences of "T"
          id.replace(toRemove, "");
          
          //Serial.println("Scanned:" + id);
          //Serial.println(id.length());
          if(id.length() == 9){
              digitalWrite(32, 0);
              Serial.println(id);
              HTTPClient http;

              String requestUrl = scriptid + "?studentid=" + id;  // Send ID as a GET parameter
              http.begin(requestUrl);

              int httpResponseCode = http.GET();
              String response = http.getString();

              Serial.println("Response: " + response);
              http.end();
          }
        }
      }
      else{
          digitalWrite(32, 0);
      }
          delay(100);
      }
    }



