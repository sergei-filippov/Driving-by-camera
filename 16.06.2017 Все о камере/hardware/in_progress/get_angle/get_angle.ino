#include <Servo.h>
Servo servo;

void setup() {
  servo.attach(45);
  Serial1.begin(9600);
  Serial.begin(9600);

}

void loop() {
  if (Serial1.available()) {
    int a = Serial1.read();
    //Serial.write(Serial.read());
    if (a >=128 ) {
      a-=256;
    }
    Serial.println(a +90);


    // delay(800);
    // Serial.println();

    servo.write(a + 90);
    // Serial.println(a+70);
  }
}
