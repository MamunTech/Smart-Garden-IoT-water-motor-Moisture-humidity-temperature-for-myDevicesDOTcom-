#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 4     // what digital pin the DHT22 is conected to
#define DHTTYPE DHT11   // there are dht11 kinds of DHT sensors

DHT dht(DHTPIN, DHTTYPE);



// WiFi network info.
char ssid[] = "WIFI USER NAME";
char wifiPassword[] = "WIFI Password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "a45f2610-befa-11e7-8978-7985115933ad";
char password[] = "84c948888f6a3aa935613a3ed2a4273a005ef60d";
char clientID[] = "e88bb1a0-befa-11e7-96e0-ed3a4c51948a";


unsigned long lastMillis = 0;

void setup() {
   pinMode(A0,INPUT);
   pinMode(16, OUTPUT);
   
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();

  /// ADC0 - CHANNEL 0  
  Cayenne.virtualWrite(0, analogRead(A0));
 Serial.println(analogRead(A0));
   Cayenne.virtualWrite(2, dht.readTemperature());
  Cayenne.virtualWrite(3, dht.readHumidity());
//  /// ADC0 - CHANNEL 2  
// Cayenne.virtualWrite(2, analogRead(A0));
// delay(500);

  
}


//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.

///  WRITE state LED  - Escribe estado LED  

CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");

   int i = getValue.asInt();
   digitalWrite(16, i);
 
}




