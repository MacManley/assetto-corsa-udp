//File: simpleserialprintlapinfo.ino

//#include "Wifi.h" // ESP32 WiFi include
#include <ESP8266WiFi.h> // ESP8266 WiFi include
#include <WiFiUdp.h>
#include <AC_UDP.h>

const char *SSID = "Your SSID";
const char *Password = "Your WiFi Password"; 
const IPAddress acServerIp(..., ..., ., ...); // Enter your consoles IP Address here

void startWiFi();

AC_Parser parser;

struct Handshaker {
    int identifier;
    int version;
    int operationId;
};


void setup() 
{ 
  Serial.begin(115200);
  startWiFi();
  pinMode(LED_BUILTIN, OUTPUT);
  parser.begin(acServerIp);
}

void loop()
{
  parser.read();
  uint32_t packetVersion = parser.packetHandshakeResponse()->handshakeResponse.version;
  Serial.println(packetVersion);
}

void startWiFi()
{
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, Password);
  Serial.print("Attempting to connect to "); 
  Serial.println(SSID);
 
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(250);
 
    if ((++i % 16) == 0)
    {
      Serial.println(F(" still trying to connect"));
    }
  }
 
  Serial.print(F("Connection Successful | IP Address: "));
  Serial.println(WiFi.localIP());
}