/**
create secrets.h in this dir.
it needs to define WIFI_SSID, WIFI_PWD, BROKER_HOST, BROKER_PORT
*/
#include "secrets.h"

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EasyButton.h>

#define CLIENT_NAME "ESP8266_1"
#define BUTTON_PIN 0
#define LED_PIN 14
#define INTERNAL_LED_PIN 2
#define MAX_LED_TIME 1023
#define NUM_BLINKS 2.0
#define SET_MAX_LED_TIME() (ledTime = millis() + MAX_LED_TIME)

WiFiClient wifiClient;
PubSubClient mqttClient(BROKER_HOST, BROKER_PORT, wifiClient);
EasyButton button(BUTTON_PIN);

unsigned long ledTime = 0;

void onPressed() {
  mqttClient.publish("global", CLIENT_NAME);
}

void callback(char* topic, byte* payload, unsigned int length) {
  SET_MAX_LED_TIME();
}

void connectToWiFiAndBroker() 
{
  Serial.print("Connecting to WIFI");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to WIFI!");

  Serial.println("Connecting to broker");
  while (!mqttClient.connect(CLIENT_NAME, "admittansen", "test")) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected to broker!");

  mqttClient.subscribe("global/#");
}

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  analogWrite(INTERNAL_LED_PIN, 255);

  Serial.begin(9600);

  button.begin();
  button.onPressed(onPressed);
  
  mqttClient.setCallback(callback);

  WiFi.begin(WIFI_SSID, WIFI_PWD);

  connectToWiFiAndBroker();
  analogWrite(INTERNAL_LED_PIN, 250);
}

void loop() 
{
  char buffer[64];
  long diffTime;

  if (!mqttClient.connected()) connectToWiFiAndBroker();
  button.read();
  mqttClient.loop();
  
  diffTime = ledTime - millis();
  if(diffTime < 0) return;

  uint8_t cos_val = (uint8_t)(255 * abs(cos(M_PI * (diffTime * NUM_BLINKS / MAX_LED_TIME) - M_PI / 2)));

  sprintf(buffer, "%u", cos_val);
  mqttClient.publish("ESP8266/CurrentValue", buffer);
  analogWrite(LED_PIN, cos_val);
}
