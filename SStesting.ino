#include "SPI.h"
#include "MFRC522.h"
#include <time.h>
#include <TimeLib.h>
#include "buzzerClass.h"

#define SS_PIN 10
#define RST_PIN 9
//#define SP_PIN 8

buzzerClass MyBuzzer (4);

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

String tag1 = "C0:2B:60:A7";
String tag2 = "A0:F0:10:A6";
String tag3 = "B7:83:82:B9";

String aTags[] = {"C0:2B:60:A7", "A0:F0:10:A6", "B7:83:82:B9"};
String ttags[2] ;
String vv[] = { "" , "" , "" , "" };

int cont = 0;
int Reset = 0;


time_t t = now();
int Timer  ;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(MyBuzzer.getpin(), OUTPUT);
}

void loop() {

  if(cont >= 1){
  Timer=second(t++);
  Serial.print(Timer);
  delay(125);
    if(Timer == 55){
    Timer = 0;
    t = 0;
    for(int i = 0 ; i<cont; i++){
        ttags[i] = vv[i];
        
      }
    cont = 0;
    
    Serial.println("");
    Serial.println("Times up...");
//    tone(4, 255);
//    delay(150);
//    noTone(4);
//    delay(150);
//    tone(4, 255);
//    delay(150);
//    noTone(4);
//    delay(150);
//    tone(4, 255);
//    delay(150);
//    noTone(4);
    MyBuzzer.MissingTagBuzz();
    }
  }
  if (!rfid.PICC_IsNewCardPresent()|| !rfid.PICC_ReadCardSerial())
  return;

  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  
  
  if(Reset == 1){
    //Timer = 0;
    Reset = 0;
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
    //Serial.println(aTags[cont]);
    //strID.substring(0) = ttags[cont];
    ttags[cont] = strID;
    Serial.println(ttags[cont]);
    cont++;
    
    Serial.println(cont);
    
    if(cont == 3){
      Serial.println("Access Allow");
//      tone(4, 150);
//      delay(300);
//      noTone(4);
      MyBuzzer.AllowAccessBuzz();
      for(int i = 0 ; i<cont; i++){
        ttags[i] = vv[i];
        
      }
      Timer = 0;
      t = 0;
      cont = 0;
    }
//    Serial.println("f");
//    Serial.println(ttags[0]);
//    Serial.println("y");
//    Serial.println(ttags[1]);
//    Serial.println("t");
//    Serial.println(ttags[2]);
//    Serial.println("e");
    
  } else {
    Serial.println("Access Denied");
//    tone(4, 255);
//    delay(2500);
//    noTone(4);
      MyBuzzer.DeniedAccessBuzz();
  }
  
  
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
