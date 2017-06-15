#include <FlexiTimer2.h>
int colour;
/*void flash() {
 
  
}  */
void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT); //red
  pinMode(3, OUTPUT); // yellow
  pinMode(4, OUTPUT); // green
 // FlexiTimer2::set(20, flash); // 500ms period
 // FlexiTimer2::start();


}

void loop() {
   Serial.print(0x03);
/*  digitalWrite(2, HIGH);
  colour = 0x00;
  delay(15000);
  digitalWrite(3, HIGH);
  colour = 0x01;
  delay(2000);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  colour = 0x02;
  delay(15000);
   digitalWrite(4, LOW);
  for (int i = 0; i < 3; i++) {
    colour = 0x03;
    digitalWrite(4, LOW);
    delay(500);
    digitalWrite(4, HIGH);
    delay(500);
  }
  digitalWrite(4, LOW);
 //  Serial.println(2);*/
}
