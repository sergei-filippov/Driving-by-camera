#include <Servo.h>
Servo servo;

void setup() {
  servo.attach(45);
  Serial1.begin(9600);
  Serial.begin(9600);

}

void loop() {
  if(Serial1.available()){
  int a = Serial1.read();
  Serial.write(a);
 // Serial.println();
servo.write(90+a);
  }

}
