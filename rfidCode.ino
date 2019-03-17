#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
//#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

String tag1 = "C0:2B:60:A7";
String tag2 = "A0:F0:10:A6";
String tag3 = "B7:83:82:B9";

String aTags[] = {"C0:2B:60:A7", "A0:F0:10:A6", "B7:83:82:B9"};
String ttags[2] ;
String vv[] = { "" , "" , "" , "" };

int cont = 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(4, OUTPUT);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()|| !rfid.PICC_ReadCardSerial())
  return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "" ;
  for(byte i = 0 ; i < 4; i++){
    strID +=
    (rfid.uid.uidByte[i]< 0x10 ? "0" : "") + 
    String(rfid.uid.uidByte[i], HEX) +
    (i != 3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);
  if(strID.substring(0) == tag1 || strID.substring(0) == tag2 || strID.substring(0) == tag3){
    ttags[cont] = strID;
    cont++;
    if(cont == 3){
    Serial.println("Access Allow");
    tone(4, 150);
    delay(300);
    noTone(4);
    delay(150);
    tone(4, 150);
    delay(300);
    noTone(4);
      for(int i = 0 ; i<cont; i++){
        ttags[i] = vv[i];
      }
      cont = 0;
    }
  } else {
    Serial.println("Access Denied");
    tone(4, 255);
    delay(2500);
    noTone(4);
  }
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
