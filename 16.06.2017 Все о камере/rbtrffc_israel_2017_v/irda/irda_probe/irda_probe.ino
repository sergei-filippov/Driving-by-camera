void setup() {
  Serial2.begin(115200);
  //Serial2.begin(115200);
  //  Serial1.begin(115200);
/*    pinMode(50,INPUT);
    pinMode(51,OUTPUT);
    pinMode(52,INPUT);
     pinMode(53,OUTPUT);*/
    digitalWrite(50,HIGH);
   //// digitalWrite(51,LOW);//-----IN
    digitalWrite(52,HIGH);
    /////digitalWrite(53,LOW);//-----IN
  Serial.begin(115200);

}

void loop() {
  if(Serial2.available()){
    Serial.println(Serial2.read());
  }
 // Serial1.print(5);
 /* if(Serial3.available()){
  Serial.println(Serial3.read());
  delay(10);}*/
  //Serial.println(Serial3.read());
   // Serial.println(Serial2.read());
   //if(Serial1.available()){
     //Serial.println(Serial1.read());
     /*if(Serial1.available()){
     
     Serial.println(Serial1.read());
   //  Serial1.print(50);
 // delay(10);
     }*/
 // Serial1.print(100);

 //Serial.println(digitalRead(53));

}               
