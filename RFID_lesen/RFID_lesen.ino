#include <SPI.h>
#include <MFRC522.h> // für RFID-RC522

#define LED_GREEN 2 // LED-Pin Green
#define LED_RED 4 // LED-Pin
#define RST_PIN 22 // RST-Pin
#define SDA_PIN 21 // SS- bzw. SDA-Pin

MFRC522 mfrc522(SDA_PIN, RST_PIN); // MFRC522-Instanz erstellen

void setup() {
  Serial.begin(115200);
  SPI.begin(); // SPI-Bus initialisieren
  mfrc522.PCD_Init(); // RFID-RC522 initialisieren
  Serial.println("Ein RFID-Tag an den Leser halten ...");
  Serial.println();
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  String rfidTag= "";
    if (mfrc522.PICC_IsNewCardPresent() && // liegt ein neues Tag vor
      mfrc522.PICC_ReadCardSerial() ) { // richtige Tag-Art
      Serial.print("RFID-Tag/Karten-ID:");
      for (byte i = 0; i < mfrc522.uid.size; i++) { // Karten-ID extrah.
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        rfidTag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        rfidTag.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      Serial.println();
      Serial.print("Aktion: ");
      rfidTag.toUpperCase();
      if (rfidTag.substring(1) == "43 BF 8C BB") { // zuzulassendes RFID-Tag
        Serial.println("Zugang genehmigt \n");
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
        delay(3000);
      } else {
        Serial.println("Zugang verweigert!\n");
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
        delay(3000);
    }
  }
}








