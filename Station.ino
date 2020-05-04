#include <esp_now.h>
#include <WiFi.h>
#include "Robot.h"

// Robot(station) initialization
Robot receiver(WiFi.macAddress());

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&receiver, incomingData, sizeof(Robot));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Dir: ");
  Serial.println(receiver.directionState);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
