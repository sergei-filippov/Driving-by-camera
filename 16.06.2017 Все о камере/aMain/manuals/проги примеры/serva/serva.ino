#include <Servo.h>
Servo servo;
void setup() {
  servo.attach(53);
  delay(1000);

}

void loop() {
 for(int i = 45; i<135;i++){
  servo.write(i);
  delay(15);
 }
for(int i=135; i>45;i--){
  servo.write(i);
  delay(15);
  
 }
 //servo.write(90);
 delay(10); 
}
