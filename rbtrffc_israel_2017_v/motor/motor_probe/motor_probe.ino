#include <Servo.h>

int i;
Servo servom;
void setup() {
pinMode(15,OUTPUT);
  servom.attach(15);
  delay(2000);
  Serial.begin(9600);
  }
void loop() {

/*  for( i = 90; i<=180; i++){
     servom.write(i);
     delay(30);
     Serial.println(i);
  }

  for( i = 180; i>0;i--){        // IT  WORKS
     servom.write(i);
     delay(30);
     Serial.println(i);
  }
  
  for(i = 0; i<=90;i++){
     servom.write(i);
     delay(30);
     Serial.println(i);
  }*/
    
 servom.write(2000);

}
