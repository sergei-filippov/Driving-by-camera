#include <Servo.h>
Servo servo;
void setup() {
  Serial1.begin(115200);
   Serial.begin(115200);
  servo.attach(53);
  delay(1000);

}

void loop() {

  if(Serial1.available()){
    int angle= Serial1.read();
    Serial.println(angle);
    servo.write(angle);
  }
/* for(int i = 45; i<135;i++){
  servo.write(i);
  delay(15);
 }
for(int i=135; i>45;i--){
  servo.write(i);
  delay(15);
  
 }
 //servo.write(90);*/
 delay(10); 
}
