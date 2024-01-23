#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/** The clock select pin for the SD card module */
#define CS_PIN 5



void readFile(fs::FS &fs, const char *path) {
  Serial.printf("lesen Quelldatei : %s\n", path);
  File file = fs.open(path);
  if (!file) {
    Serial.println("lesendes Öffnen der Datei gescheitert");
    return;
  }

  Serial.print("gelesener Inhalt : ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("in Zieldatei schreiben : %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("schreibendes Öffnen der Datei gescheitert");
    return;
  }

  if (file.print(message)) {
    Serial.println("\"" + String(message) + "\" in Zieldatei geschrieben");
  } else {
    Serial.println("Schreibzugriff gescheitert");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("an Zieldatei anfügen : %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Anfügendes Öffnen der Datei gescheitert");
    return;
  }
  if (file.print(message)) {
    Serial.println("Text an Dateiinhalt angefügt");
  } else {
    Serial.println("Anfügen gescheitert");
  }
  file.close();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void setup() {

  // Initialize the Serial (it'll tell us if the program runned correctly)
  Serial.begin(9600);
  while (!Serial) { }

  // Check the module is connected
  if (!SD.begin(CS_PIN)) {
    Serial.println("Error, SD Initialization Failed");
    return;
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
    Serial.println("Kartentyp nicht erkannt");
    return;
  }
  writeFile(SD, "/test.txt", "Hallo ");
  appendFile(SD, "/test.txt", "ESP332 SD-Karte!\n");
  readFile(SD, "/test.txt");
}

void loop() {
}
