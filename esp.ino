#include <Wire.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "tests-6fa58.firebaseio.com"
#define FIREBASE_AUTH "5aHsBXNnyEeXklIayIX3229CTXmEt2m1b2zFm6g1"
#define WIFI_SSID "Connect_4G_Router"
#define WIFI_PASSWORD "Aa2468Aa"

void setup() {
 Serial.begin(9600); /* begin serial for debug */
 Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
   if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  Serial.println(Firebase.getString("message"));
  Serial.println("hhhhhhhhhhhhhhh");
  int totatTags = Firebase.getInt("/logs/numberTags");
  int ccont = 1;
  String Tag = Firebase.getString("/logs/tag1");
  String Tag2 = Firebase.getString("/logs/tag2");
  int tagLn = Tag.length();
  Serial.println(totatTags);
  Serial.println(Tag);
  Serial.println(tagLn);
  Serial.println("eeeeeeeeeeeeeeennnnnnnnnnnnddddddddd");
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
 Wire.beginTransmission(8); /* begin with device address 8 */
 //Wire.write("I am Yazeed From ESP");  /* sends hello string */
 Wire.write(totatTags);
 Wire.write(tagLn);
 if(ccont == 1){
 for(int i = 0; i < tagLn; i++){
  Wire.write(Tag.charAt(i));
 }
 ccont++;
 }else if(ccont == 2){
  for(int i = 0; i < tagLn; i++){
  Wire.write(Tag2.charAt(i));
 }
 ccont++;
 }
 Wire.endTransmission();    /* stop transmitting */

 Wire.requestFrom(8, 24); /* request & read data of size 13 from slave */
 
 
 
 while(Wire.available()){
    char c = Wire.read();
  Serial.print(c);
 }
 Serial.println();
 delay(1000);
}
