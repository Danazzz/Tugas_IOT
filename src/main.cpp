//include library yang diperlukan
#include <Arduino.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// sensor  ds18b20 disambungkan di pin 4
#define ONE_WIRE_BUS 4

//menggunakan wifi-tethering
const char* WIFI_SSID = "FTI";
const char* WIFI_PASS = "teknikpastijaya";
const char* HOSTNAME = "DANA";

//berikan nama variabel untuk syntax onewire dan dallastemperature
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//function untuk membaca temperature suhu
float getAmbientTemperature(){
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  float tempC = sensors.getTempCByIndex(0); //temperatur celcius
  if(tempC != DEVICE_DISCONNECTED_C){
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    return tempC;
  } 
  else{
    Serial.println("Error: Could not read temperature data");
    return -127;
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

  sensors.begin(); //menjalankan sensor
}

void loop()
{
  //menjalankan function getAmbientTemperature()
  float suhu = getAmbientTemperature();
  delay(5000);
}