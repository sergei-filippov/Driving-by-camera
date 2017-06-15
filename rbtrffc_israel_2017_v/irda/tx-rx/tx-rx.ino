void setup() {
  Serial3.begin(115200);
  Serial1.begin(115200);
    Serial2.begin(115200);
  Serial.begin(115200);

}

void loop() {
  //Serial.println(Serial3.read());
   // Serial.println(Serial2.read());
   
    // Serial1.println(1000);
/*  Serial2.println(1005);
 if(Serial2.available()){
  Serial.println(Serial2.read());
 }*/
 Serial.println(Serial3.read());
// Serial.println(Serial2.read());
 //Serial.println(Serial1.read());
 delay(10);
 // delay(10);
 // Serial1.print(100);

}               
