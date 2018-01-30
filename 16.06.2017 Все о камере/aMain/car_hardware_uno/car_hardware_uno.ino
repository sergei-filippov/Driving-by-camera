#include <Servo.h>
#include <SoftwareSerial.h>


Servo servo;

SoftwareSerial angleReceive(6, 7); // RX, TX      // to be able to receive angle from seeduino

SoftwareSerial irdaSignal(11, 12); // RX, TX      //irda connection


//------------------------------//irda codes
#define red 0
#define red_yellow  1
#define yellow  4
#define green  2
#define blinking_green  3
#define pedestrian_crossing  5
#define stop_sign 6
//------------------------------//
//#define potentiometer 53

int currentspeed ;
int speed1, irda, d1, d2, d3, distanceEdge, speedBeforCrossing, slowSpeed, incomingByte, angle;
bool debug = 1;
bool stopline;

const char buzzer = 13;
const char distSensor0 = A0;
const char distSensor1 = A1;
const char distSensor2 = A2;
//----------------------//motor driver - pins
const char inaPin = 2;    //defines direction of rotating
const char inbPin = 4;
const char pwm = 3;      //values from 0 - 255

void setup() {
  for (int i = 0; i < 1000; i++) {
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, HIGH);
    delay(1);
    digitalWrite(buzzer, LOW);
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
  pinMode(distSensor0, INPUT);
  pinMode(distSensor1, INPUT);
  pinMode(distSensor2, INPUT);

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
    Serial.begin(115200);    //pc connection
  }

  angleReceive.begin(9600);
  irdaSignal.begin(115200);

  speed1 = 70;         // usual speed
  currentspeed = speed1;      // speed when...

  distanceEdge = 15;   // max distance without barrier

}

void loop() {
  //Serial.println(irda);
  analogWrite(pwm, currentspeed);  //start the engine

  //------------------------------------------------------------------------// check signals

  /*if (Serial2.available()) {
      irda = Serial2.read();
      Serial.println(irda);
    }*/
  if (irdaSignal.available()) {
    irda = irdaSignal.read();
    Serial.println(irda);
    if ((irda == 0) || (irda == 1) || (irda == 4)) {  //if red,red+yellow,yellow
      currentspeed = 0;

    }
    for (int i = 0; i < 64; i++) {
      Serial.available();
    }
    irdaSignal.overflow();
  } else {
    currentspeed = speed1;
  }


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
  /*   if (irdaSignal.available()) {
       irda = irdaSignal.read();
        if (irda == 6) {
          analogWrite(pwm, 0);
          delay(5000);

        }
      }
  */
  //------------------------------------//
  //---------------------------------------------------------------------//distance attributive
  d1 = 5222 / (analogRead(distSensor0) - 13);    //changes values into cm
  d2 = 5222 / (analogRead(distSensor1) - 13);
  d3 = 5222 / (analogRead(distSensor2) - 13);

  if ((d1 > 0) && (d2 > 0) && (d3 > 0)) {  // some wrong values
    if ((d1 <= distanceEdge) || (d2 <= distanceEdge) || (d3 <= distanceEdge)) {

      currentspeed = 0;
      /*     if (debug) {
             Serial.print(d1);
             Serial.print(" ");
             Serial.print(d2);
             Serial.print(" ");
             Serial.print(d3);
             Serial.println(" ");
           }*/
      // delay(1000);

    }
  }else{
    currentspeed = speed1;
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
    }

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
