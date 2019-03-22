
// digit pot
#define UD  12                         // выходы к которым подключен модуль
#define INC 11
#define CS  10
#define readd  A3
//


void setup()  {
  //delay(500);
  
  //digit pot
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH); 
  delay(1);
 // digitalWrite(CS, LOW); 

   // to_down();              

  Serial.begin(115200);

  pinMode(readd, INPUT);
  
  //Serial.println(-20);
  //Serial.println(analogRead(A0));
  for(int i =0;i<50;i++){
    Serial.println(1024);
  }

  delay(500);
   for(int i =0;i<50;i++){
    Serial.println(analogRead(readd));
  }


 

  delay(500);
  for(int i =0;i<100;i++){
    // down
  digitalWrite(UD, LOW);
  digitalWrite(INC, HIGH);
  digitalWrite(CS, LOW);
  delay(1);
  digitalWrite(INC, LOW);
  delay(1);               
  digitalWrite(CS, HIGH);
  Serial.println(analogRead(readd));
  }
  
   delay(500);

  for(int i =0;i<100;i++){
  digitalWrite(UD, HIGH);             // на U/D подаем единицу
  digitalWrite(INC, HIGH);            // и на INC тоже
  digitalWrite(CS, LOW);              // включаем микросхему
  delay(1);               // ждем
  digitalWrite(INC, LOW);             // дергаем вход INC
  delay(1);
  digitalWrite(CS, HIGH);

    Serial.println(analogRead(readd));

  }



  for(int i =0;i<60;i++){
    // down
  digitalWrite(UD, LOW);
  digitalWrite(INC, HIGH);
  digitalWrite(CS, LOW);
  delay(1);
  digitalWrite(INC, LOW);
  delay(1);               
  digitalWrite(CS, HIGH);
  Serial.println(analogRead(readd));
  }
  
   delay(2000);

  for(int i =0;i<30;i++){
  digitalWrite(UD, HIGH);             // на U/D подаем единицу
  digitalWrite(INC, HIGH);            // и на INC тоже
  digitalWrite(CS, LOW);              // включаем микросхему
  delay(1);               // ждем
  digitalWrite(INC, LOW);             // дергаем вход INC
  delay(1);
  digitalWrite(CS, HIGH);

    Serial.println(analogRead(readd));

  }
}

void up(){
  //up
  
}


void loop() {
  

 while(true) {}

}
