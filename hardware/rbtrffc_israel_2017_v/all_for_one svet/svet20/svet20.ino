#include <Servo.h>

Servo servo;
Servo servom;

int distStop = 10;
int dist, cm, svet, svet1, svet2, black, white, midLight;
int servoRange = 1800 - 1050; // range of values of serva
float rotation, svetRange;         //roatain *
int k = 1080;                  // rotation +
int speed1 = 0;            // normal speed

void buzz1sec() {
  for (int i = 0; i < 500; i++) {
    digitalWrite(10, HIGH);
    delay(1);
    digitalWrite(10, LOW);
    delay(1);

  }
}

void setup() {
  pinMode(15, OUTPUT); // motor
  servo.attach(14);    //1050 - straight right   1800 - straight left
  servom.attach(15);
  delay(2000);
  Serial.begin(9600);
  pinMode(10, OUTPUT); // buzz
  pinMode(27, INPUT);  // button
  pinMode(A8, INPUT);  // svet // levo
  pinMode(A7, INPUT);  // svet // pravo
  pinMode(15, OUTPUT); // serva
  pinMode(A6, INPUT);  // dist
  digitalWrite(27, HIGH);

  //---------------------------------------------------------------//
  while (true) {
    bool flag = 0;
    if (digitalRead(27) == LOW) {
      buzz1sec();

      black = analogRead(A7);
      while (true) {
        if (digitalRead(27) == LOW) {
          buzz1sec();
          delay(1000);
          white = analogRead(A7);                     //----------------------------// detecting white and black values at this very place
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        break;
      }
    }
  }
 /* Serial.println(white);
  Serial.println(black);
  svetRange = white - black;
  rotation = servoRange / svetRange;
  Serial.print(svetRange);
  Serial.print(" ");
  Serial.print(servoRange);
  Serial.print(" ");
  Serial.println(rotation);*/
}
//----------------------------------------------------------------------//
void loop() {

  //servom.write(speed1);        //  speed things

  //-----------------------------------------------------------------------------//driving
  svet1 = analogRead(A7);          // white-850; black - 220
  svet2 =  analogRead(A8);
  svet = svet1 - svet2;

   servo.write((svet * rotation) + k);

 /* Serial.println(svet);
  Serial.println(rotation);
  Serial.println(svet * rotation) + k;*/



  // servo.write();


  //-----------------------------------------------------------------//

  //-------------------------------------------------------------------------------//
  
  Serial.println((5222 / (analogRead(A6) - 13)));
  if ((5222 / (analogRead(A6) - 13)) <= distStop) {
  
   /* while (true) {
      servom.write(0);                                                                   // stop in case of another car
      Serial.println(1000);
    }*/
  }
  //-------------------------------------------------------------------------------------//
}
