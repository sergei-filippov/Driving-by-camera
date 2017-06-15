int d, rowA6; // расстояние и значения с датчика
void setup() {
  Serial.begin(9600);
 // pinMode(A10,INPUT);
  pinMode(A14,INPUT);

}

void loop() {
  rowA6=analogRead(A14);
 Serial.println(rowA6);
  Serial.print(" ");
d=5222/(rowA6-13);
  Serial.println(d);
  delay(200);

}
