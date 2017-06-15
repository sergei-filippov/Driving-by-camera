#include <Servo.h>
Servo servo;
int p;
int r;

bool f;
void setup() {
  servo.attach(16);
  Serial.begin(9600);
  pinMode(A6,INPUT);

}
void loop() {
  p=analogRead(A6); //40-340 = 300
  r=5222/(p-13);
  servo.write(r);   
   Serial.print(p);
    Serial.print("-");
    Serial.println(r);
 
 

  
  

}
