void setup() {
 pinMode(A6,INPUT); // pravo
  pinMode(19,INPUT); //levo
 Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A6));
  delay(10);

}
