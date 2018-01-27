#include <Servo.h>
#include <SoftwareSerial.h>


Servo servo;

SoftwareSerial angleReceive(6, 7); // RX, TX


//------------------------------//irda codes
#define red 0
#define red_yellow  1
#define yellow  4
#define green  2
#define blinking_green  3
#define pedestrian_crossing  5
#define stop_sign 6
//------------------------------//
#define potentiometer 53

int speed1, irda, d1, d2, d3, distanceEdge, speedBeforCrossing, slowSpeed, incomingByte;
bool debug = 0;
bool stopline;
int angle;


//----------------------//motor driver - pins
const char inaPin = 2;
const char inbPin = 4;
const char pwm = 3;


void num_all(int n) {
  switch (n) {

    case 0: num0(); break;
    case 1: num1(); break;
    case 2: num2(); break;
    case 3: num3(); break;
    case 4: num4(); break;
    case 5: num5(); break;
    case 6: num6(); break;
    case 7: num7(); break;
    case 8: num8(); break;
    case 9: num9(); break;
  }
}
void num0()
{
  digitalWrite(6, LOW); digitalWrite(7, LOW);
  digitalWrite(8, LOW); digitalWrite(9, LOW);
  digitalWrite(10, LOW); digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void num1()
{
  num3();
  digitalWrite(6, HIGH); digitalWrite(9, HIGH); digitalWrite(12, HIGH);
}

void num2()
{
  num8();
  digitalWrite(8, HIGH); digitalWrite(11, HIGH);
}

void num3()
{
  num8();
  digitalWrite(10, HIGH); digitalWrite(11, HIGH);
}

void num4()
{
  num9();
  digitalWrite(6, HIGH); digitalWrite(10, HIGH); digitalWrite(9, HIGH);
}

void num5()
{
  num8();
  digitalWrite(10, HIGH); digitalWrite(7, HIGH);
}

void num6()
{
  num8();
  digitalWrite(6, HIGH); digitalWrite(7, HIGH);
}

void num7()
{
  num1();
  digitalWrite(6, LOW);
}

void num8()
{
  num0();
  digitalWrite(12, LOW);
}

void num9()
{
  num8();
  digitalWrite(10, HIGH);
}
int pwm_encoder(int pwmstart) {
  int encoder_pwm = pwmstart, pwm01, pwm10, t1, t2 = 0;
  t1 = millis();
  while (t2 - t1 < 30000) {
    t2 = millis();

    while (digitalRead(3) == 0) {
      if (digitalRead(2) == 0) {
        encoder_pwm--;
        break;
      }
    }
    delay(10);

    while (digitalRead(2) == 0) {
      if (digitalRead(3) == 0) {
        encoder_pwm++;
        break;
      }
    }
    pwm10 = encoder_pwm / 10;
    pwm01 = encoder_pwm % 10;
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    num_all(pwm01);
    delay(10);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    num_all(pwm10);
  }
  //Serial.println(encoder_pwm);
  return (encoder_pwm);
}


void setup() {
  for (int i = 0; i < 1000; i++) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
    delay(1);
    digitalWrite(13, LOW);
    delay(1);
  }
  // -----------------------------------------------//encoder
  /*  pinMode(2, INPUT); pinMode(3, INPUT); // encoder               // pins 2-12 are reserved

    pinMode(6, OUTPUT); pinMode(7, OUTPUT);
    pinMode(8, OUTPUT); pinMode(9, OUTPUT);
    pinMode(10, OUTPUT); pinMode(11, OUTPUT);
    pinMode(12, OUTPUT); pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
  */


  //------------------------------//distance detectors
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  
  angleReceive.begin(9600);

  servo.attach(5);   //possible values 55-125
  delay(1000);        // doesn't work without

  //-------------------------------------------//motor driver
  pinMode(inaPin, OUTPUT);   //num 5 on driver
  pinMode(inbPin, OUTPUT);   //num 4 on driver
  pinMode(pwm, OUTPUT);      //num 3 on driver




  //-------------------------//motors
  digitalWrite(inaPin, LOW);
  digitalWrite(inbPin, HIGH);

  if (debug) {
    Serial.begin(9600);    //pc connection
  }

  // Serial1.begin(9600);   //seeeduino angle
  // Serial2.begin(115200); //irda
  // Serial3.begin(115200); //seeeduino stop line



  speed1 = 70;         // usual speed
  distanceEdge = 15;   // max distance without barrier
  slowSpeed = 50;      // speed when...

  // speed1=pwm_encoder(speed1);
}

void loop() {

  analogWrite(pwm, speed1);  //start the engine

  //------------------------------------------------------------------------// check signals

  /*if (Serial2.available()) {
      irda = Serial2.read();
      Serial.println(irda);
    }*/
  /* if (Serial2.available()) {
     irda = Serial2.read();
     if ((irda == 0) || (irda == 1) || (irda == 4)) {  //if red,red+yellow,yellow
       Serial.println(irda);
       analogWrite(pwm, 0);
       delay(50);
     }
    }
  */

  /*
       //----------------------------------//pedestrian crossing
     if (Serial2.available()) {
       if (Serial2.read() == 5 ) {
         analogWrite(pwm, slowSpeed);
       }
     }

     //----------------------------------//
  */


  //----------------------------------// stop sigh
  /*     if (Serial2.available()) {
         if (Serial2.read() == 6) {
           analogWrite(pwm, 0);
           delay(5000);

         }
       }
  */
  //------------------------------------//
  //---------------------------------------------------------------------//distance attributive
    d1 = 5222 / (analogRead(A0) - 13);    //changes values into cm
    d2 = 5222 / (analogRead(A1) - 13);
    d3 = 5222 / (analogRead(A2) - 13);

    if ((d1 > 0) && (d2 > 0) && (d3 > 0)) {  // some wrong values
      if ((d1 <= distanceEdge) || (d2 <= distanceEdge) || (d3 <= distanceEdge)) {





        analogWrite(pwm, 0);
        if (debug) {
          Serial.print(d1);
          Serial.print(" ");
          Serial.print(d2);
          Serial.print(" ");
          Serial.print(d1);
          Serial.println(" ");
        }
        delay(100);

      }
    }
  //---------------------------------------------//stopline + irda

  /* if (Serial3.available()) {
     int read1 = Serial3.read();
     /* Serial.print(read1);
       Serial.print(" \n");*/
  /*  if (read1 == 1) {
      if (Serial2.available()) {
        irda = Serial2.read();

        while ((irda == 0) || (irda == 1) || (irda == 4) || (irda == 6) || (irda == 3) ) //if red,red-yellow,yellow,stop sign, blinking green
        {

          //Serial.println(irda);
          analogWrite(pwm, 0);
          delay(100);
          //servo.write(45);
          irda = Serial2.read();
        }

      }
    }
    }*/

  /*
    irda = Serial2.read();
    if (irda == 0 || irda == 1 || irda == 4) {
      speed1 = speedBeforCrossing;
    }
  */
  //------------------------------------------------------------//
  //-----------------------------//stopline
  /* if (Serial3.available()) {
     stopline = Serial3.read();
     Serial.println(stopline);
     if (stopline) {
       speed1 = 0;
       Serial.print("STOP");
     }
    }
  */
  //-----------------------------------------------------------//read from camera
  if (angleReceive.available()) {
    // incomingByte = Serial1.read();

    angle = angleReceive.read();

    //    Serial.print(" ");
    if (angle > 128)
    {
      angle -= 256;
    }

    angle *= -2;   // mechanic coefficient
    if (angle > 36 || angle < -36) {
      speed1 = 50;
    } else {
      speed1 = 50;
    }
    angle = angle + 90;

    //
         //Serial.print(angle);
    //   Serial.print(" ");

    servo.write(angle);




    //  delay(10);
    //Serial.print(incomingByte);

  }
  //----------------------------------------------------------//
  /*if (Serial1.available() > 0) {
      // read the oldest byte in the serial buffer:
      incomingByte = Serial1.read();
      Serial.print(incomingByte);
      Serial.print(" \n");
    }*/




}
