#include <Servo.h>

Servo servo;


//------------------------------//irda codes
//--------------------------------------------------// i'm really not sure in the this defining
#define red 0
#define red_yellow  1
#define yellow  4
#define green  2
#define blinking_green  3
#define pedestrian_crossing  5
#define stop_sign 6
//------------------------------//

int angle, speed1, irda, d1, d2, d3, distanceEdge, speedBeforCrossing, slowSpeed;

bool stopline;


const int inaPin = 26;
const int inbPin = 27;
const int pwm = 3;
const int diagaPin = 24;
const int diagbPin = 25;
int incomingByte;
void setup() {

  //-----------------//distance detectors
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  //----------------//
  servo.attach(20);    //serva 55-125
  delay(1000);
  pinMode(inaPin, OUTPUT);   //5
  pinMode(inbPin, OUTPUT);   //4
  pinMode(pwm, OUTPUT);   //3
  pinMode(diagaPin, INPUT);  //7
  pinMode(diagbPin, INPUT);  //8


  //pinMode(40, INPUT);     //stop-line existence



  digitalWrite(inaPin, LOW); // for motors
  digitalWrite(inbPin, HIGH);

  Serial.begin(115200);
  Serial1.begin(115200); //seeeduino angle
  Serial2.begin(115200); //irda

  Serial3.begin(115200); //seeeduino stop line
  speed1 = 40;

  Serial3.begin(115200); //stopline
  speed1 = 70;

  distanceEdge = 20;
  slowSpeed = 50;
}

void loop() {
  if(Serial2.available()){
    irda = Serial2.read();
    if(irda == 0 || irda == 1 || irda == 4){
      analogWrite(pwm,0);
    }
  }
  analogWrite(pwm, speed1);
  //----------------------------------------------------------//
  //----------------------------------//pedestrian crossing
/*  if (Serial2.available()) {
    if (Serial2.read() == 5 ) {
      analogWrite(pwm, slowSpeed);
    }
  }

  //----------------------------------//
  //------------------------------------------------------------// stop sigh
  if (Serial2.available()) {
    if (Serial2.read() == 6) {
      analogWrite(pwm, 0);
      delay(5000);

    }
  }*/
  //------------------------------------------------------------//
  //----------------------------------//distance attributive
  /*  d1 = 5222 / (analogRead(A6) - 13);                     //probably it changes values into cm
    d2 = 5222 / (analogRead(A7) - 13);
    d3 = 5222 / (analogRead(A8) - 13);
      if ((d1 <= distanceEdge) || (d2 <= distanceEdge) || (d3 <= distanceEdge)) {
        while ((1 <= distanceEdge) || (d2 <= distanceEdge) || (d3 <= distanceEdge)) {

          d1 = 5222 / (analogRead(A6) - 13);
          d2 = 5222 / (analogRead(A7) - 13);
          d3 = 5222 / (analogRead(A8) - 13);
          analogWrite(pwm, 0);
        //  Serial.println(d1);
       //   Serial.print(" ");
       //   Serial.println(d2);
       //   Serial.print(" ");
       //   Serial.println(d3);


        }


      }*/
 /* d1 = 5222 / (analogRead(A6) - 13);
  d2 = 5222 / (analogRead(A7) - 13);
//  if (( d2 <= distanceEdge) || (d2 <= distanceEdge)) {
    while ((d2 <= distanceEdge) || (d2 <= distanceEdge)) {
      d2 = 5222 / (analogRead(A7) - 13);
      d1 = 5222 / (analogRead(A6) - 13);
      analogWrite(pwm, 0);
   //   Serial.println(d2);
//    }
  }*/

  //----------------------------------//
  //------------------------------------------------------------//irda things

  /*  irda = Serial2.read();
     if (irda == 0 || irda == 1 || irda == 4) { //if red,red+yellow,yellow
      speed1 = speedBeforCrossing;
      //program should wait for a stopline more intently. It helps to differ a crossing and a stopline.
     }
  */
  //------------------------------------------------------------//
  //---------------------------------------------//stopline + irda
  /*if (digitalRead(40) == 1) {
    speed1 = 0;
    Serial.print("STOP");

    }*/
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

  irda = Serial2.read();
  if (irda == 0 || irda == 1 || irda == 4) { //if red,red+yellow,yellow
    speed1 = speedBeforCrossing;

  }

  //------------------------------------------------------------//
  //---------------------------------------------//stopline
  if (Serial3.available()) {
    stopline = Serial3.read();
    Serial.println(stopline);
    if (stopline) {
      speed1 = 0;
      Serial.print("STOP");
    }
  }


  //-----------------------------------------------//
  //-----------------------------------------------------------//read from camera
  if (Serial1.available()) {
    // incomingByte = Serial1.read();

    angle = Serial1.read();

    //    Serial.print(" ");
    /*if (angle > 256)
        {
          angle -= 256;
        }*/
    angle -= 60;
    if ((angle < 12) && (angle > -12))

    angle = Serial1.read() + 90;
    //     Serial.print(angle);
    //   Serial.print(" ");
    if (angle > 156)

    {
      servo.write((angle * 1.2) + 90);
    }

    else
      servo.write((angle * 2.8) + 90);
    // angle = (angle * 1.7) + 90;
    //Serial.println((angle * 1.5) + 90);
    //  Serial.println(angle);
    //  delay(10);
    //servo.write((angle * 1.5) + 90);

    //    Serial.println(angle);

    //  delay(10);
    //  Serial.print(angle);
    //Serial.print(incomingByte);

    //  Serial.print(" \n");

    //    Serial.print(" \n");

  }
  //----------------------------------------------------------//
  /*if (Serial1.available() > 0) {
      // read the oldest byte in the serial buffer:
      incomingByte = Serial1.read();
      Serial.print(incomingByte);
      Serial.print(" \n");
    }*/




}
