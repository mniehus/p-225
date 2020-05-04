#include <esp_now.h>
#include <WiFi.h>
#include "Robot.h"

// WiFi credentials
const char* ssid     = "";
const char* password = "";

// Web Server and header
WiFiServer server(80);
String header;

// Station mac address
uint8_t stationAddress[] = {0x24, 0x6F, 0x28, 0x10, 0x5C, 0x48}; // ESP32 DevKit
//uint8_t stationAddress[] = {0x3C, 0x71, 0xBF, 0xAF, 0xCB, 0x60}; // ESP32 CAM

// Robot initialization
Robot robot(WiFi.macAddress());

// ESP-Now communication (direction)
void sendDirection();

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP_STA);

  // Setting up the robot motors pins
  robot.setupRobot();

  // Connection to the wifi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Local IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  // Registration of the station peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, stationAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Verification of the connection
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  WiFiClient client = server.available();   
  
  if (client) {                             
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {            
        char c = client.read();          
        Serial.write(c);               
        header += c;
        if (c == '\n') {              
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /frontleft") >= 0) {
              Serial.println("Direction - FRONTLEFT.");
              robot.moveRobot(FRONTLEFT);
              sendDirection();
            } else if (header.indexOf("GET /forward") >= 0) {
              Serial.println("Direction - FORWARD.");
              robot.moveRobot(FORWARD);
              sendDirection();
            } else if (header.indexOf("GET /frontright") >= 0) {
              Serial.println("Direction - FRONTRIGHT.");
              robot.moveRobot(FRONTRIGHT);
              sendDirection();
            } else if (header.indexOf("GET /left") >= 0) {
              Serial.println("Direction - LEFT.");
              robot.moveRobot(LEFT);
              sendDirection();
            } else if (header.indexOf("GET /stop") >= 0) {
              Serial.println("Direction - STOP.");
              robot.moveRobot(STOP);              
              sendDirection();
            } else if (header.indexOf("GET /right") >= 0) {
              Serial.println("Direction - RIGHT.");
              robot.moveRobot(RIGHT);
              sendDirection();
            } else if (header.indexOf("GET /backleft") >= 0) {
              Serial.println("Direction - BACKLEFT.");
              robot.moveRobot(BACKLEFT);
              sendDirection();
            } else if (header.indexOf("GET /backward") >= 0) {
              Serial.println("Direction - BACKWARD.");
              robot.moveRobot(BACKWARD);
              sendDirection();
            } else if (header.indexOf("GET /backleft") >= 0) {
              Serial.println("Direction - BACKLEFT.");
              robot.moveRobot(BACKLEFT);
              sendDirection();
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { text-align: center;font-family: Helvetica;margin: 0px auto;display: inline-block;}");
            client.println("p {margin: 0 0 0 0;padding: 0 0 0 0;}");
            client.println(".button {background-color: silver;padding: 40px;border-color: gray;cursor: pointer;}</style></head>");
            
            client.println("<body><h1>Mini Robot Controller</h1>");
            
            client.println("<p><a href=\"/frontleft\"><button class=\"button\"></button></a><a href=\"/forward\"><button class=\"button\"></button></a><a href=\"/frontright\"><button class=\"button\"></button></a></p>");
            client.println("<p><a href=\"/left\"><button class=\"button\"></button></a><a href=\"/park\"><button class=\"button\"></button></a><a href=\"/right\"><button class=\"button\"></button></a></p>");
            client.println("<p><a href=\"/backleft\"><button class=\"button\"></button></a><a href=\"/backward\"><button class=\"button\"></button></a><a href=\"/backright\"><button class=\"button\"></button></a></p>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}

void sendDirection() {
  esp_err_t result = esp_now_send(stationAddress, (uint8_t *) &robot, sizeof(Robot));
   
  if (result == ESP_OK) {
    Serial.println("Direction sent with success,");
  }
  else {
    Serial.println("Erro while sending the direction.");
  }  
}
