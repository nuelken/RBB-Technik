/** This program tests the SD card module is working */
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2  // Digital pin connected to the DHT sensor | Digitaler Pin, der mit dem DHT-Sensor verbunden ist
#define CS_PIN 5

#define DHTTYPE DHT11  // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

/** The clock select pin for the SD card module */


void setup() {
  Serial.begin(300);
  // Initialize device. | Gerät initialisieren.
  dht.begin();
  sensor_t sensor; 
  // Initialize the Serial (it'll tell us if the program runned correctly)

  while (!Serial) { }

  // Check the module is connected
  if (!SD.begin(CS_PIN)) {
    Serial.println("Error, SD Initialization Failed");
    return;
  }

  write();
  //read();

}

void write() {

  // Delay between measurements. | Verzögerung zwischen den Messungen.
  delay(delayMS);
  // Get temperature event and print its value. | Abrufen des Temperaturereignisses und ausgabe seines Wertes.
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  
  File dataFile = SD.open("/Daten.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(F("Temperature: "));
    dataFile.println(event.temperature);
    //dataFile.println(F("°C");
    dataFile.close();
    Serial.println("Success, data written to Daten.txt");
  } else {
    Serial.println("Error, couldn't not open Daten.txt");
  }
}
/*
void read() {
  File testFile = SD.open("/SDTest.txt", FILE_READ);
  if (testFile) {
    Serial.print("Read from file: ");
    while(testFile.available()){
        Serial.write(testFile.read());
    }
    testFile.close();
    Serial.println("Success, data read from SDTest.txt");
  } else {
    Serial.println("Error, couldn't not read SDTest.txt");
  }
}
*/

// Do nothing, sd card operations run on setup()
void loop() {}