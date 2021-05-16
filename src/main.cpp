//include library yang diperlukan
#include <Arduino.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <MQTT.h>
// sensor  ds18b20 disambungkan di pin 4
#define ONE_WIRE_BUS 4

//menggunakan wifi-tethering
const char* WIFI_SSID = "FTI";
const char* WIFI_PASS = "teknikpastijaya";
const char* HOSTNAME = "DANA";
const char* IOTBROKER = "broker.hivemq.com";

//berikan nama variabel untuk syntax onewire dan dallastemperature
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//wifi dan MQTT client
WiFiClient net;
MQTTClient iot;

//function untuk membaca temperature suhu
float getAmbientTemperature(){
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  float tempC = sensors.getTempCByIndex(0); //temperatur celcius
  float tempF = sensors.getTempFByIndex(0);//temperatur farenheit

  //if else statement
  if(tempF != DEVICE_DISCONNECTED_F){
    if(tempC != DEVICE_DISCONNECTED_C){
      Serial.print("Celcius temperature for the device 1 (index 0) is: ");
      Serial.print(tempC);
      Serial.println("°C");
    }
    else{
      Serial.println("Error: Could not read temperature data");
      return -127;
    }
    Serial.print("Fahrenheit temperature for the device 1 (index 0) is: ");
    Serial.print(tempF);
    Serial.println("°F");
    return tempF;
  } 
  else{
    Serial.println("Error: Could not read temperature data");
    return -196.6;
  }
}

void setup()
{
  //menjalankan serial monitor
  Serial.begin(115200);

  //koneksi ke Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.setHostname(HOSTNAME);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("WiFi connected successfully.");

  Serial.println("--DS18B20 Demo--");
  sensors.begin(); //menjalankan sensor

  iot.begin(IOTBROKER, net);
}

void loop()
{
  //menjalankan function getAmbientTemperature()
  getAmbientTemperature();
  delay(5000);
}