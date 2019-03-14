
// digit pot
#define UD  10                         // выходы к которым подключен модуль
#define INC 11
#define CS  12
//



int digitpot_pos=0;  
bool digitpot_direct=1; // 0 -down // 1-up


void setup()  {
  //delay(500);
  
  //digit pot
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH); 
   // to_down();              

  Serial.begin(115200);

  pinMode(A0, INPUT);
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);



  float a=analogRead(A0);
  float v = (a/1024);
  float r2 = (9900*v)/(5-v);

  Serial.println(a);

  for(int i =0;i<100;i++){
    down();

    float a=analogRead(A0);
    
    float v = (a/1024);
    float r2 = (9900*v)/(5-v);

    Serial.println(a);
  }


  for(int i =0;i<100;i++){
    up();
    
    float a=analogRead(A0);
    
    float v = (a/1024);
    float r2 = (9900*v)/(5-v);

    Serial.println(a);
  }



  
  
  delay(60); 

}

void to_down(){
  for(int i=0;i<100;i++){
    down();
  }
  digitpot_direct=1;
  digitpot_pos=0;
}


void to_upx(int x){
  for(int i=0;i<x;i++){
    up();
  }
  digitpot_direct=0; //
  digitpot_pos=x;
}

void up(){                            // поднимает ползунок в верх на 1 ступень
  digitalWrite(UD, HIGH);             // на U/D подаем единицу
  digitalWrite(INC, HIGH);            // и на INC тоже
  digitalWrite(CS, LOW);              // включаем микросхему
  delayMicroseconds(1);               // ждем
  digitalWrite(INC, LOW);             // дергаем вход INC
  delayMicroseconds(1);
  digitalWrite(INC, HIGH);
  delayMicroseconds(1);
  digitalWrite(INC, LOW);                  // в этом случаи положение ползунка записано не будет
  digitalWrite(CS, HIGH);             // выключаем микросхему и записываем положение в EEPROM 
}

void down(){                          // опускаем ползунок в верх на 1 ступень
  digitalWrite(UD, LOW);
  digitalWrite(INC, HIGH);
  digitalWrite(CS, LOW);
  delayMicroseconds(1);
  digitalWrite(INC, LOW);
  delayMicroseconds(1);
  digitalWrite(INC, HIGH);
  delayMicroseconds(1);
  digitalWrite(INC, LOW);                  // в этом случаи положение ползунка записано не будет
  digitalWrite(CS, HIGH);
}



void loop() {
  
  

}
