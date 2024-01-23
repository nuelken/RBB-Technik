/*lesen und schreiben ein RFID Chip*/

#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 22 // RST-Pin
#define SDA_PIN 21 // SS- bzw. SDA-Pin

MFRC522 mfrc522(SDA_PIN, RST_PIN); // Objekt bilden
MFRC522::StatusCode status;
MFRC522::MIFARE_Key key;
byte block = 5; // zu bearbeitender Block

void rfidLesen(){
  Serial.print("rfidLesen ");
  Serial.print("Inhalt Block 5: ");
  byte bufferRd[18];  // muss mind. 2 Byte größer
                      // als Block sein
  byte len = 18;

  status = mfrc522.MIFARE_Read(block, bufferRd, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Lesen fehlgeschlagen: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  
  for (uint8_t i = 0;i< 16; i++) {
    Serial.write(bufferRd[i]);
  }
  Serial.println();
  Serial.println("RFID-Lesen Ende");
  return;
}

void rfidSchreiben() {
  byte buffer[16] ={'M', 'u', 's', 't', 'e', 'r', 'm', 'a', 'n', 'n'};
  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Schreiben fehlgeschlagen ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else Serial.println("RFID schreiben erfolgreich");
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Ein RFID-Tag an den Leser halten ...");
  Serial.println();
}

void loop() {
  for (byte i = 0;i< 6; i++) { // alten Key löschen
    key.keyByte[i] = 0xFF;
  }
  if (mfrc522.PICC_IsNewCardPresent() &&
    mfrc522.PICC_ReadCardSerial()){
    Serial.println("Karte erkannt:");

    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print("Authentifikation fehlgeschlagen: ");
      Serial.println(mfrc522.GetStatusCodeName(status));
    } else {
      rfidLesen();
      rfidSchreiben();
      rfidLesen();
    }
    Serial.println(); }
      
  delay(1000);
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
