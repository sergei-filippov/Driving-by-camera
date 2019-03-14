#define UD  2                          // выходы к которым подключен модуль
#define INC 3
#define CS  4

void up(){                            // поднимает ползунок в верх на 1 ступень
  digitalWrite(UD, HIGH);             // на U/D подаем единицу
  digitalWrite(INC, HIGH);            // и на INC тоже
  digitalWrite(CS, LOW);              // включаем микросхему
 // delayMicroseconds(1);               // ждем
  digitalWrite(INC, LOW);             // дергаем вход INC
 // delayMicroseconds(1);
  //digitalWrite(INC, HIGH);
 // delayMicroseconds(1);
 // digitalWrite(INC, LOW);                  // в этом случаи положение ползунка записано не будет
  digitalWrite(CS, HIGH);             // выключаем микросхему и записываем положение в EEPROM 
}

void down(){                          // опускаем ползунок в верх на 1 ступень
  digitalWrite(UD, LOW);
  digitalWrite(INC, HIGH);
  digitalWrite(CS, LOW);
  //delayMicroseconds(1);
  digitalWrite(INC, LOW);
 // delayMicroseconds(1);
 // digitalWrite(INC, HIGH);
 // delayMicroseconds(1);

  digitalWrite(CS, HIGH);
}

void setup() {
  Serial.begin(9600);

  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);                         // выключаем микросхему
}

void loop() {

 for(int i =0;i<100;i++){
  up();
  delay(20); 
 }

 for(int i =0;i<100;i++){
  down();
  delay(20); 
 }

}
