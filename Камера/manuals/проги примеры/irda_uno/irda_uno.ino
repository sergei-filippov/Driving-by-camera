#include <SoftwareSerial.h>

SoftwareSerial irdaSignal(11, 12); // RX, TX      //irda connection\

int irda;
void setup() {
 
    Serial.begin(115200);    //pc connection
  
  irdaSignal.begin(115200);
irdaSignal.listen();
}

void loop() {
  
 /* if(irdaSignal.available()){
    Serial.println(irdaSignal.read());
   
  }*/
  
   if(irdaSignal.available()){
  irda = irdaSignal.read();
  
    Serial.println(irda);
   delay(500);
  }
//delay(1000);
//Serial.println(456);
}
