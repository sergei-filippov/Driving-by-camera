#include <Servo.h>

int i,led, delay_t=0, di=1;
Servo servom;
void setup() {
pinMode(13,OUTPUT);
pinMode(15,OUTPUT);
  servom.attach(15);
  delay(2000);
  Serial.begin(9600);
  
   for(led = 0; led<10; digitalWrite (13,1), delay (100), digitalWrite (13,0), delay (100),led++);
}
void loop() {

  for( i = 1500; i<=2000;i=i+di){
     servom.write(i);
     delay(delay_t);
    // Serial.println(i);
  }
  //servom.write(0);
  //delay (2000);
  //di=-di;
   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}
  
  for( i = 2000; i>=1000;i--){        // IT  WORKS
     servom.write(i);
     delay(delay_t);
    // Serial.println(i);
  }
     for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}

    for(i = 1000; i<=1500;i++){
     servom.write(i);
     delay(delay_t);
    // Serial.println(i);
  }   
   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}

// servom.write(1);
}
