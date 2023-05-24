#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#define LED_PIN 3
#define SET_PIN 4

const char* ssid = "SSID";
const char* pass = "PASSWORD";
const IPAddress ip(192,168,1,10);
const IPAddress subnet(255,255,255,0);

WiFiServer server(1337);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SET_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(SET_PIN, LOW);
  

  // Wifi setup
  if(!WiFi.config(ip,ip,subnet)) {
    Serial.println("Failed to configure!");
  }
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  server.begin();
  Serial.println("Server begin");
}

void loop() {
  WiFiClient client = server.available();

  if(client) {
    Serial.println("New Client");
    while(client.connected()) {
      digitalWrite(LED_PIN, LOW);
      int size = client.available();
      if(size) {
        String c = client.readString();
        if(c == "TurnOn") {
          Serial.println("TurnON");
          digitalWrite(SET_PIN, HIGH);
        }else if(c == "TurnOff") {
          Serial.println("TurnOFF");
          digitalWrite(SET_PIN, LOW);
        }
      }
    }
  }
  client.stop();
  digitalWrite(LED_PIN, HIGH);
}