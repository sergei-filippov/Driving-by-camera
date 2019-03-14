
// digit pot
#define UD  2                          // выходы к которым подключен модуль
#define INC 4 
#define CS  3
//
int digitpot_pos=0;  
bool digitpot_direct=0; // 0 -down // 1-up

void setup()  {
  
  //digit pot
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);                         // выключаем микросхему
  //


  Serial.begin(9600);
  to_down();
  
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
  //digitalWrite(INC, LOW);                  // в этом случаи положение ползунка записано не будет
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

  digitalWrite(CS, HIGH);
}

void to_down(){
  for(int i=0;i<100;i++){
    down();
  }
  digitpot_direct=1;
  digitpot_pos=0;
}

void to_up(){
  for(int i=0;i<100;i++){
    up();
  }
  digitpot_direct=0;
  digitpot_pos=100;
}

void loop() {

 /*
  to_up();
  delay(1000);
  to_down();
  delay(1000); 
  */

  //digit pot
    if(digitpot_direct){
      up();
      digitpot_pos++;
    }
    else{ 
      down();
      digitpot_pos--;
    }
    if(digitpot_pos>100 || digitpot_pos<0){
      digitpot_direct=!digitpot_direct;
    }
  
    Serial.print(digitpot_pos);
    Serial.print(" ");
    Serial.println(digitpot_direct);

    delay(20);



}
