
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  Serial1.begin(115200);
  
}

void loop() {
  // see if there's incoming serial data:
  if (Serial1.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial1.read();
    Serial.print(incomingByte);
    Serial.print(" \n");
  }
}
