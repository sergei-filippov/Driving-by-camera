#include <Servo.h>

Servo servo;


//------------------------------//irda codes
#define red 0
#define red_yellow  1
#define yellow  4
#define green  2
#define blinking_green  3
#define pedestrian_crossing  5
#define stop_sign 6
//------------------------------//

int angle, speed1, irda, d1, d2, d3, distanceEdge, speedBeforCrossing, slowSpeed, incomingByte;;

bool stopline;


//----------------------//motor driver - pins
const int inaPin = 26;
const int inbPin = 27;
const int pwm = 3;
const int diagaPin = 24;
const int diagbPin = 25;

void setup() {

  //-----------------//distance detectors
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);

  servo.attach(20);   //possible values 55-125
  delay(1000);        // doesn't work without

  //-------------------------------------------//motor driver
  pinMode(inaPin, OUTPUT);   //num 5 on driver
  pinMode(inbPin, OUTPUT);   //num 4 on driver
  pinMode(pwm, OUTPUT);      //num 3 on driver
  pinMode(diagaPin, INPUT);  //num 7 on driver
  pinMode(diagbPin, INPUT);  //num 8 on driver



  //-------------------------//motors 
  digitalWrite(inaPin, LOW);
  digitalWrite(inbPin, HIGH);


  Serial.begin(9600);    //pc connection
  Serial1.begin(9600);   //seeeduino angle
  Serial2.begin(115200); //irda
  Serial3.begin(115200); //seeeduino stop line



  speed1 = 70;         // usual speed
  distanceEdge = 20;   // max distance without barrier
  slowSpeed = 50;      // speed when...
}

void loop() {

  analogWrite(pwm, speed1);  //start the engine


  //------------------------------------------------------------------------// check signals
  if (Serial2.available()) {
    irda = Serial2.read();
    if (irda == 0 || irda == 1 || irda == 4) {  //if red,red+yellow,yellow
      analogWrite(pwm, 0);
    }
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

/*    
    //----------------------------------// stop sigh
    if (Serial2.available()) {
      if (Serial2.read() == 6) {
        analogWrite(pwm, 0);
        delay(5000);

      }
    }
 */
  //------------------------------------//
  //---------------------------------------------------------------------//distance attributive
  d1 = 5222 / (analogRead(A6) - 13);    //changes values into cm
  d2 = 5222 / (analogRead(A7) - 13);
  d3 = 5222 / (analogRead(A8) - 13);
  
  if ((d1 <= distanceEdge) || (d2 <= distanceEdge) || (d3 <= distanceEdge)) {     // if there're barriers
    while ((d1 <= distanceEdge) || (d2 <= distanceEdge) || (d3 <= distanceEdge)) {
      
      d1 = 5222 / (analogRead(A6) - 13);
      d2 = 5222 / (analogRead(A7) - 13);
      d3 = 5222 / (analogRead(A8) - 13);
      analogWrite(pwm, 0);
      /*Serial.println(d1);
        Serial.print(" ");
        Serial.println(d2);
        Serial.print(" ");
        Serial.println(d3);
      */
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
  if (Serial3.available()) {
    stopline = Serial3.read();
    Serial.println(stopline);
    if (stopline) {
      speed1 = 0;
      Serial.print("STOP");
    }
  }

  //-----------------------------------------------------------//read from camera
  if (Serial1.available()) {
    // incomingByte = Serial1.read();

    angle = Serial1.read();

    //    Serial.print(" ");
    if (angle > 128)
    {
      angle -= 256;
    }

    anngle*=2;     // mechanic coefficient

    angle = angle + 90;
    Serial.println(angle);
    //     Serial.print(angle);
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
