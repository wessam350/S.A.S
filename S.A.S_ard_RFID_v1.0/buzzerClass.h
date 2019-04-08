class buzzerClass{

private:
int pin;
  
  public:
  buzzerClass(int buz){
    pin = buz;
    
  }

  public:
  void AllowAccessBuzz(){
    tone(4, 150);
    delay(300);
    noTone(4);
  }

  void DeniedAccessBuzz(){
    tone(4, 255);
    delay(2500);
    noTone(4);
  }

  void MissingTagBuzz(){
    
    tone(4, 255);
    delay(150);
    noTone(4);
    delay(150);
    tone(4, 255);
    delay(150);
    noTone(4);
    delay(150);
    tone(4, 255);
    delay(150);
    noTone(4);
  }
  int getpin(){
    return pin ;
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  };
