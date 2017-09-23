#include <Servo.h>
Servo servo;
int k = 4;
bool sign;  //0 -- -; //1 -- +
void setup() {
  servo.attach(45);
  Serial1.begin(9600);
  Serial.begin(9600);

}

void loop() {
  if (Serial1.available()) {
    int a = Serial1.read();
    a = a & B01111111;
    //Serial.write(Serial.read());
  /*  if (a >=128 ) {
      a-=256;
      sign=0;
    }*/
    
    a*=k;
   // Serial.println((a +90));


    // delay(800);
     //Serial.println();

    servo.write((a + 90));
    Serial.println((a +90));

 

    // Serial.println(a+70);
  }
}
