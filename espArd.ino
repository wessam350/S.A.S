#include <Wire.h>
String s;
String tagT;
String tagT2;
String LTags[1];
int totatTags;
int tagLn;
int coont = 0;
char c;
void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
}

void loop() {
 delay(100);
}
      
// function that executes whenever data is received from master
void receiveEvent(int howMany) {
// while (0 <Wire.available()) {
//    char c = Wire.read();      /* receive byte as a character */
//    Serial.print(c);           /* print the character */
//  }

  totatTags = Wire.read();
  tagLn = Wire.read();
  Serial.println("tag ln");
  Serial.println(tagLn);
  if(coont == 0){
  for(int i = 0; i < tagLn; i++){
    c = Wire.read();
     tagT += c;
  }
  Serial.println("1");
  LTags [coont] = tagT;
  Serial.println(LTags [coont]);
  tagT = "";
  coont++;
  }else if(coont == 1){
      for(int i = 0; i < tagLn; i++){
    c = Wire.read();
     tagT2 += c;
  }
  Serial.println("2");
  LTags [coont] = tagT2;
  Serial.println(LTags [coont]);
  tagT2 = "";
  coont++;
  }
  
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
 Wire.write("I am Wessam From Arduino");  /*send string on request */
}
