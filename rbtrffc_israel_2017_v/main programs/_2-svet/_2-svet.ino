#include <FlexiTimer2.h>
#include <Servo.h>

Servo servo;
Servo servom;

int distStop = 20;
int dist, cm, svet, svet1, svet2, black, white, midLight, signalIr, stopLine;
int servoRange = 1800 - 1050; // range of values of serva
float rotation, svetRange;         //rotation * // range of possible lighting
int k = 1450;                  // rotation +
int speed1 = 1620;            // normal speed

//---------------------------------------------------------------------------------------------------------//IRDA
void flash() {
  if (Serial2.available()) {
    stopLine = analogRead(A6);
    signalIr = Serial2.read();
    if (signalIr == 0 || signalIr == 1 || signalIr == 4 || signalIr == 3 || signalIr == 5) {     //red //red+yellow // yellow // blinking green // pedestrian crossing
      speed1 = 1600;                                            // starts moving slower
      if (stopLine <= midLight) {                              // car on a stop line //
        speed1 = 1500;                                       // car stops
      }
    }
  }
}
//----------------------------------------------------------------------------------------------------------//  BUZZ
void buzz1sec() {
  for (int i = 0; i < 500; i++) {
    digitalWrite(10, HIGH);
    delay(1);
    digitalWrite(10, LOW);
    delay(1);

  }
}
//-----------------------------------------------------------------------------------------------------------//
void setup() {
  //FlexiTimer2::set( 50, flash);
  //FlexiTimer2:: start();
  servo.attach(14);    //1050 - straight right   1800 - straight left
  delay(1000);
  servom.attach(15);
  delay(1000);        //never delete
  Serial.begin(9600);
  Serial2.begin(115200); //irda  !!!!
  // servo.write(120);

  pinMode(10, OUTPUT); // buzz
  pinMode(27, INPUT);  // button
  pinMode(A9, INPUT);  // stopLine
  pinMode(A8, INPUT);  // svet // levo
  pinMode(A7, INPUT);  // svet // pravo
  // pinMode(15, OUTPUT); // motor
  // pinMode(14, OUTPUT); // serva
  pinMode(A6, INPUT);  // dist
  digitalWrite(27, HIGH);   // pull-up for button

  //---------------------------------------------------------------------------------------------------------//
  while (true) {
    bool flag = 0;
    if (digitalRead(27) == LOW) {
      black = analogRead(A7);
      buzz1sec();
      while (true) {
        if (digitalRead(27) == LOW) {
          white = analogRead(A7);
          buzz1sec();
          delay(1000);
          //----------------------------// detecting white and black edge values at this very place
          flag = 1;
          break;
        }
      }
      if (flag == 1) {
        break;
      }
    }
  }
  midLight = (white + black) / 2;
  svetRange = white - black;
  rotation = servoRange / (2 * svetRange);

  Serial.println(white);
  Serial.println(black);
  Serial.print(2 * svetRange);
  Serial.print(" ");
  Serial.print(servoRange);
  Serial.print(" ");
  Serial.println(rotation);

}
//-----------------------------------------------------------------------------------------------//
void loop() {

  servom.write(speed1);        //  speed things

  //-----------------------------------------------------------------------------//driving
  svet1 = analogRead(A7);          // white-850; black - 220
  svet2 =  analogRead(A8);
  svet = svet1 - svet2;

  servo.write(1500 + (svet / 1.7));
  //servo.write(1500+svet);

  /* Serial.print(svet1);
     Serial.print(" ");
     Serial.println(svet2);*/
  // Serial.println(rotation);
  /* Serial.print(svet);
    Serial.print(" ");
    Serial.println(1500+(svet*rotation));*/
  Serial.println((svet * rotation) + k);



  // servo.write(130);
  //delay(100);


  //-----------------------------------------------------------------//

  //-------------------------------------------------------------------------------//
  /*Serial.println(analogRead(A6));
    Serial.println((5222 / (analogRead(A6) - 13)));*/
  /*  if ((5222 / (analogRead(A6) - 13)) <= distStop) {

      while (true) {
        servom.write(0);                                                                   // stop in case of another car
        Serial.println(1000);
      }
    }*/
  //-------------------------------------------------------------------------------------//

}
