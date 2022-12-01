/*
Made By:
####### #     # ######   #####    ###     #   
#       #  #  # #     # #     #  #   #   ##   
#       #  #  # #     # #       #     # # #   
#####   #  #  # ######  #       #     #   #   
#       #  #  # #   #   #       #     #   #   
#       #  #  # #    #  #     #  #   #    #   
#######  ## ##  #     #  #####    ###   ##### 

 http://arduino.esp8266.com/stable/package_esp8266com_index.json To setup your boards
*/

//Imports and Libs
#define BLYNK_PRINT Serial 
#include <Ultrasonic.h> //https://github.com/ErickSimoes/Ultrasonic
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Const values provided by Blynk App Web
#define BLYNK_TEMPLATE_ID "TMPLwqUBmhYB"
#define BLYNK_DEVICE_NAME "Temperatura y Humedad Este Si"
#define BLYNK_AUTH_TOKEN "EdLfQRxIRBIzOwMIYdE4NxzTDpP9vQM2"



//Temperature and humidity Sensor
#include "DHT.h" // https://github.com/adafruit/DHT-sensor-library  https://github.com/adafruit/Adafruit_Sensor
#define DHTPIN 2 //Pin of DHT 
#define DHTTYPE DHT11 //Define your type of DHT

//Constant of Wi-Fi, values may change
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Familia_Rodriguez";
char pass[] = "Rodriguez1234";



//Widgets of Virtual LEDS and Virtual Pins
WidgetLED led1(V2); //Virtual Pins
WidgetLED led2(V3); //Virtual pins
WidgetLED led3(V4); //Virtual Pins

// Values of DHT
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer; //Define the var of timer

Ultrasonic ultrasonic(12, 14);

//Void to get Temperature from sensor
void getTemperature()
{
  float h = dht.readHumidity(); //Read Humidity 
  float t = dht.readTemperature(); //  dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!"); //Catch Error
    return;
  }
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h); //Virtual Pin for humidity
  Blynk.virtualWrite(V6, t); //Virtual Pin for temperature
}

//Void to get Distance an qty of garbage from sensor
void sendSensor()
{
  float distanceSensor = ultrasonic.distanceRead();
  //Conditional To  turn on Led when reach some value 
    if (isnan(distanceSensor)) {
      Serial.println("Failed To Read the data");
      return;
    }
    Blynk.virtualWrite(V1, distanceSensor);
     if (distanceSensor <= 25){
    led1.on();
    led2.off();
    led3.off();
    }
    else if (distanceSensor <= 50) {
      led2.on();   
      led1.off();
      led3.off();
    }
    else if (distanceSensor >= 75) {
      led3.on();  
      led2.off();
      led1.off(); 
    }
    else{
      led1.off();
      led2.off();
      led3.off();
    }
    //End of conditional
}


void setup()
{
  // Debug console
  Serial.begin(9600); //Start the serial monitor for catch errors
  dht.begin(); //Start Store data
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //Start the session
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080); Change for this if dont work first
  timer.setInterval(1000L, sendSensor); //Set time and call the function
  timer.setInterval(1000L, getTemperature); //Set time and call the function
}

void loop()
{
  Blynk.run(); //Call the function Blynk
  timer.run(); //Call the function timer
}

/*
-Members Of Group:
 -Wilfredo Rodriguez
 -Mauricio Martinez
 -Adonay Aragon
 -Carlos Nieto
 -Wilder Romero
 -Alejandro Garcia

-Proyect:
Garbage Monitoring System for networking fair
 
 */

