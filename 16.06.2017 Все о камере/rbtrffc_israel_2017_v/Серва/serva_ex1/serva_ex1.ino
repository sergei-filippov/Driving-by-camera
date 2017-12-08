#include <Servo.h>
Servo servo;
int p;
bool f;
void setup() {
  servo.attach(20);
 // delay(1000);
  Serial.begin(9600);
  servo.write(120);

}

void loop() {

  servo.write(90);
  delay(500);
  servo.write(88);
  delay(500);
  
/*  // servo.write(125);
 // Serial.println(servo.read());
 //servo.write(60);
  for(int i =45;i<135;i++){
    Serial.println(i);
    servo.write(i);
      delay(30);
  }*/
 /* for(int i =135;i>45;i--){
    Serial.println(i);
    servo.write(i);
      delay(30);
  }*/
   /*// p=map( analogRead(14), 0, 1023, 0, 180);
   p=analogRead(14);
    Serial.println(p);
  if(p> 1024){
    servo.write(p-1024);
  }else{
    servo.write(p+1000);
  }*/

 }
