#include <Wire.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "a-e6f51.firebaseio.com"
#define FIREBASE_AUTH "rOqyHybXNvivVDMQ0mQIpRg3EghNPb1XddCzhcLJ"
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
  int totatTags = Firebase.getInt("/TagOn/yvlxVz25GCNEHyZMIhHflojL5Pw2/Tagon"); //to get the total tags of the user

  String Tag = Firebase.getString("/TagOn/yvlxVz25GCNEHyZMIhHflojL5Pw2/tg1"); //takeing the fist tag of the user
  
  String tagPath = "/TagOn/yvlxVz25GCNEHyZMIhHflojL5Pw2/tg"; //saveing the tag path 
  int tagLn = Tag.length(); //geting the length of the tag from the first tag
  Serial.println(totatTags);
  Serial.println(tagLn);
  Serial.println("---------------->>**<<----------------");
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
 Wire.beginTransmission(8); /* begin with device address 8 */
 
 Wire.write(totatTags); //sending the total tags of the user
 Wire.write(tagLn); //sending the tag length
 

  for(int i = 1; i <= totatTags; i++){ //this loop is for reading all tags from the database
    String thePathTag = tagPath + i; //takeing the path of the tag and adding the (i) int of the to crate the full path of the tag
    String fTag = Firebase.getString(thePathTag); //reading the tag from database and saving it in to (fTag)
    Serial.println("------------");
    Serial.println(fTag);
    fTag.remove(2,1); //we needed to remove the (:) from the tag 
    fTag.remove(4,1);   // so that we can send not mor than 32 byet
    fTag.remove(6,1);     // we removed the (:) from 2 removing 1, from 4 removing 1, from 6 removing 1
    Serial.println("============");
    Serial.println(fTag);
    for(int i = 0; i < 8; i++){ //a loop for sending
    Wire.write(fTag.charAt(i));   //  the tag after removing the (:)
 }
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
