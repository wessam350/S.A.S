#include "SPI.h"
#include "MFRC522.h"
#include <time.h>
#include <TimeLib.h>
#include "buzzerClass.h"
#include <Wire.h>

#define SS_PIN 10
#define RST_PIN 9

buzzerClass MyBuzzer (4);

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;
String tag1 = ""; //kkk
String tag2 = ""; //sss
String tag3 = ""; //fff

String tempTag[2] ;
String tempEmpty[] = { "" , "" , "" , "" };

int cont = 0;

//-----------------
String espTag;
String LTags[1];
int totalTags;
int tagLn;
char c;
String arrTags[2];
//-----------------

time_t t = now();
int Timer  ;

void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
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
        tempTag[i] = tempEmpty[i];
        
      }
    cont = 0;
    
    Serial.println("");
    Serial.println("Times up...");

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
  Serial.println("");
  
  if(strID.substring(0) == arrTags[0] || strID.substring(0) == arrTags[1] || strID.substring(0) == arrTags[2]){
    tempTag[cont] = strID;
    Serial.println(tempTag[cont]);
    cont++;
    
    Serial.println(cont);
    
    if(cont == totalTags){
      Serial.println("Access Allow");

      MyBuzzer.AllowAccessBuzz();
      for(int i = 0 ; i<cont; i++){
        tempTag[i] = tempEmpty[i];
        
      }
      Timer = 0;
      t = 0;
      cont = 0;
    }
    
  } else {
    Serial.println("Access Denied");

      MyBuzzer.DeniedAccessBuzz();
  }
  
  
  
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
void receiveEvent(int howMany) {

  totalTags = Wire.read();
  tagLn = Wire.read();
  Serial.println("tag ln");
  Serial.println(tagLn);
  

  Serial.println("1");
  

  
   for(int i = 0; i < totalTags; i++){
    for(int ii = 0; ii < 8; ii++){
    c = Wire.read();
    espTag += c;
     if(ii == 1 || ii == 3 || ii == 5){
      espTag += ':';
     }
    }
    Serial.println("------------------++++++++++++");
    Serial.println(espTag);
    arrTags[i] = espTag;
    Serial.println("++++++++++++++++++------------");
    Serial.println(arrTags[i]);
    Serial.println("++++++++++++++++++------------");
    espTag = "";
   
   }
       

  
  
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 //Wire.write("I am Wessam From Arduino");  /*send string on request */
}
