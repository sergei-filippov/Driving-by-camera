#include <Servo.h>
Servo servo;

int angle, speed1;
const int inaPin = 26;  //26
const int inbPin = 27;   //27
const int pwm = 3;  //2
const int diagaPin = 24;  //24
const int diagbPin = 25;   //25
void setup() {

  servo.attach(14);
  delay(1000);
  //------------------------------------------------// MOTOR PINS
  pinMode(inaPin, OUTPUT);   //50
  pinMode(inbPin, OUTPUT);   //4
  pinMode(pwm, OUTPUT);   //6
  pinMode(diagaPin, INPUT);  //7
  pinMode(diagbPin, INPUT);  //8

  digitalWrite(inaPin, HIGH);  //DIRECTION
  digitalWrite(inbPin, LOW);
  //-----------------------------------------------------//
  Serial.begin(115200);
  Serial1.begin(115200);
  speed1 = 70;
}

void loop() {
  /* angle = Serial1.read();
    //  delay(10);
    servo.write(angle + 45);
    Serial.println(angle);
  */
  servo.write(90);
  analogWrite(pwm, speed1);   //MOTOR

  /* Serial.print(analogRead(diagaPin));
     Serial.print(" ");
     Serial.println(analogRead(diagbPin));
     delay(500);*/
}











