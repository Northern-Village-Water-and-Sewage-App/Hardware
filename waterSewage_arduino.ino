//#include <WiFiEsp.h>
//#include <WiFiEspClient.h>
//#include <WiFiEspServer.h>
//#include <WiFiEspUdp.h>


#include "SoftwareSerial.h"
#include <NewPing.h>
#define TRIGGER_PIN  7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     6  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define TANK_OWNER 1
#define TANK_MODEL_WATER 1
#define TANK_MODEL_SEWAGE 1
#define SEWAGE_WARN_PIN 3
#define SEWAGE_FULL_PIN 4
// set up software serial to allow serial communication to our TX and RX pins
SoftwareSerial Serial1(10, 11);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


// Set  baud rate of so we can monitor output from esp.
#define ESP8266_BAUD 9600



void setup()
{
  pinMode(SEWAGE_WARN_PIN, INPUT);
  pinMode(SEWAGE_FULL_PIN, INPUT);
  // initialize serial for debugging
  Serial.begin(9600);
  // initialize serial for ESP module
  Serial1.begin(ESP8266_BAUD);


  }


void loop()
{
if (Serial1.available() > 0) {
  String input =  Serial1.readString();
  Serial.println("Received " + input);

 if (input == "water") { 
    Serial.println("Connected to server");
           unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
    Serial.print("Ping: ");
    int value = 80 - (uS / US_ROUNDTRIP_CM);
    Serial.print(value); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm");
    //String pushdata = "GET /test/write_data.php?value=" + String(value) + ", " + String(TANK_OWNER) + ", " + String(TANK_TYPE) + ", " + String(TANK_MODEL);
    String pushdata = "GET /test/write_data_water.php?value=" + String(value) + ","+String(TANK_OWNER)+","+String(TANK_MODEL_WATER);
    //Serial.println(pushdata);
    //String pushdata = "GET /test/test.php HTTP/1.1";
 //  bool waiting = true;
 //  String values;
 //   while(waiting)
 //   {   
    Serial1.print(pushdata); //one
    Serial.print("sending to esp-01(" + pushdata + ")");
  //   if (Serial1.available() > 0) { //one
    // read the incoming byte:
 //   values = Serial1.readString(); //one
 //   if(values == "done")
 //   {
 //   waiting = false;
 //   }
    
  //   }
     delay(2000);
 //   }
  }
    if (input == "sewage") { 
    Serial.println("Connected to server");
    String value = "OK";
    String values;
    if (digitalRead(SEWAGE_WARN_PIN) == HIGH)
    {    
      if (digitalRead(SEWAGE_FULL_PIN) == HIGH)
      {
      value = "%27CRITICAL%27";
      }
      else
    {
      value = "%27WARNING%27";
    }
    }
    else
    {
      value = "%27OK%27";
    }
    Serial.print("Value: ");
    Serial.println(value); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)

    //String pushdata = "GET /test/write_data.php?value=" + String(value) + ", " + String(TANK_OWNER) + ", " + String(TANK_TYPE) + ", " + String(TANK_MODEL);
    String pushdata = "GET /test/write_data_sewage.php?value=" + String(value) + "," + String(TANK_OWNER)+"," + String(TANK_MODEL_SEWAGE);

 //  bool waiting = true;
 //   while(waiting)
 //   {   
    Serial1.print(pushdata); //one
    Serial.print("sending to esp-01(" + pushdata + ")");
 //    if (Serial1.available() > 0) { //one
    // read the incoming byte:    
 //   values = Serial1.readString(); //one
 //   if(values == "done")
 //   {
 //   waiting = false;
 //   }
    
 //    }
     delay(2000);
 //   }
  
  
  
  }


}
Serial.print(".");
delay(1000);
}
