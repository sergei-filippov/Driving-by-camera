#include <SoftwareSerial.h>

SoftwareSerial irdaSignal(11, 12); // RX, TX      //irda connection\

int irda;
void setup() {
 
    Serial.begin(115200);    //pc connection
  
  irdaSignal.begin(115200);

}

void loop() {
  //irda = irdaSignal.read();
  if(irdaSignal.available()){
    Serial.println(irdaSignal.read());
   
  }

//Serial.println(456);
}
