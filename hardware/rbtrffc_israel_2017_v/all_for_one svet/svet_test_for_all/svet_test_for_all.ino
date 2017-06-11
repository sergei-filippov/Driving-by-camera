void setup() {
  pinMode(27, INPUT); //button
  pinMode(A6, INPUT); // pravo1
  pinMode(A7, INPUT); // pravo2
  pinMode(A8, INPUT); // pravo3
  pinMode(A9, INPUT); // pravo4
  pinMode(A10, INPUT); // pravo5
  pinMode(A11, INPUT); // pravo6

  pinMode(19, INPUT); //levo
  Serial.begin(9600);
  while (true) {
    if (digitalRead(27) == LOW) {
      Serial.println(analogRead(A6));
      Serial.println(analogRead(A7));
      Serial.println(analogRead(A8));
      Serial.println(analogRead(A9));
      Serial.println(analogRead(A10));
      Serial.println(analogRead(A11));
      break;
    }


  }
}

void loop() {

}
