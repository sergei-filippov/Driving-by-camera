#include <FlexiTimer2.h>
#include <Servo.h>

Servo servo;
Servo servom;

int distStop = 20;
int dist, cm, svet, svet1, svet2, black1, white1, black2, white2, midLight, signalIr, stopLine, flag;
int servoRange = 1800 - 1050; // range of values of serva
float svet2Range, svet1Range;
float  svetRange;         //rotation * // range of possible lighting
float k2To1;                // coefficient that change svet2Range to svet1Range
float k1Toservo;            // coefficient that change svet2Range to servoRange
int speed1 = 1680;            // normal speed

//---------------------------------------------------------------------------------------------------------//IRDA
void flash() {
  if (Serial3.available()) {
    stopLine = analogRead(A6);
    signalIr = Serial3.read();
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
    flag = 0;
    if (digitalRead(27) == LOW) {
      black1 = analogRead(A7);
      black2 = analogRead(A8);
      flag = 1;
      buzz1sec();
      while (true) {
        if (digitalRead(27) == LOW) {
          white1 = analogRead(A7);
          white2 = analogRead(A8);
          buzz1sec();
          break;
        }
      }
      if (flag == 1) {
        break;
      }
    }
  }


  svet1Range = white1 - black1;
  svet2Range = white2 - black2;
  k2To1 = svet1Range / ( svet2Range);
  k1Toservo = servoRange / (2* svet1Range) ;

 // Serial.println( k2To1 = svet1Range / ( svet2Range));
  Serial.println( svet1Range);
  Serial.println( svet2Range);
  Serial.print(k2To1);
  Serial.print(" ");
  Serial.print(k1Toservo);
  Serial.print(" ");

}
//-----------------------------------------------------------------------------------------------//
void loop() {

  servom.write(speed1);        //  speed things

  //-----------------------------------------------------------------------------//driving
  svet1 = analogRead(A7);          // white-850; black - 220
  svet2 =  analogRead(A8);
  svet = svet1 - (svet2 * k2To1);

  servo.write(svet * k1Toservo + 1500);
  //servo.write(1500+svet);

  Serial.print(svet1);
  Serial.print(" ");
  Serial.println(svet2 * k2To1);
  Serial.println((svet * k1Toservo + 1500));
  /* Serial.print(svet);
    Serial.print(" ");
    Serial.println(1500+(svet*rotation));*/




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
