#include <Servo.h>
Servo servo;

int angle, speed1;
const int inaPin = 26;  //26
const int inbPin = 27;   //27
const int pwm = 3;  //2
const int diagaPin = 24;  //24
const int diagbPin = 25;   //25
int incomingByte;
void setup() {
  pinMode
  servo.attach(14);
  delay(1000);
  pinMode(inaPin, OUTPUT);   //50
  pinMode(inbPin, OUTPUT);   //4
  pinMode(pwm, OUTPUT);   //6
  pinMode(diagaPin, INPUT);  //7
  pinMode(diagbPin, INPUT);  //8

  pinMode(40,INPUT);      //stop-line existens 
  digitalWrite(inaPin, LOW); // for motors
  digitalWrite(inbPin, HIGH);

  Serial.begin(115200);
   Serial1.begin(115200);
  speed1 = 70; 
}

void loop() {
 // servo.write(65);              //serva 55-125
/* for(int i =55;i<115;i+=2){
  servo.write(i);
  delay(40);
 }*/
 if(digitalRead(40)==1){
   speed1=0;
   Serial.print("STOP");
   
 }
  if(Serial1.available()){
   // incomingByte = Serial1.read();
  angle = Serial1.read()+90;
  Serial.print(angle);
   Serial.print(" ");
  if (angle > 156)
  {
    angle -= 256;
  }
   Serial.println(angle);
  //  delay(10);
   servo.write(angle);
 //  Serial.print(angle);
      //Serial.print(incomingByte);
      Serial.print(" \n");
  }
/*if (Serial1.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial1.read();
    Serial.print(incomingByte);
    Serial.print(" \n");
}*/
   analogWrite(pwm, speed1);
   
 /* Serial.print(analogRead(diagaPin));
    Serial.print(" ");
    Serial.println(analogRead(diagbPin));
    delay(500);*/
}
