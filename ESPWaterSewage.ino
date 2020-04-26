/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//#define STASSID "TP-LINK_DF17"
//#define STAPSK  ""


//const char* ssid     = STASSID;
//const char* password = STAPSK;

const char* host = "192.168.0.194";
const uint16_t port = 80;
String values = "";
void setup() {
  Serial.begin(9600);
delay(5000);
  // We start by connecting to a WiFi network
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
if(!wifiManager.autoConnect("AutoConnectAP")) {
    //Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  } 

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */

 

  delay(6000);
}
void sendData(String request)
{
   WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  if (client.connected()) {
    Serial.println("connected");
    bool waiting = true;
    while(waiting)
    {
      Serial.print(request);
      delay(5000);
     if (Serial.available() > 0) {
    // read the incoming byte:
    values = Serial.readString();
    waiting = false;

     }
        delay(4000);
    }//String("GET /test/write_data.php?value=7,%201,%201,%201")
    Serial.print(values);
    client.print( values+ " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
   //          "Connection: close\r\n" +
             "\r\n"
            );
    Serial.print("done");
        client.stop();
    while(Serial.available() > 0) {
    char t = Serial.read();
     }
     unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      //Serial.println(">>> Client Timeout !");
      client.stop();
      delay(20000);
      return;
    }
  }
     delay(10000);
}
}
void loop() {
  sendData("sewage");
  sendData("water");
    delay(300000);

  

  // wait for data to be available
  
}

 
