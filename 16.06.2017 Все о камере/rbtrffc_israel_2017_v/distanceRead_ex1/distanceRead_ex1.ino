int d, row13,row14,row15,row12; // расстояние и значения с датчика
void setup() {
  Serial.begin(9600);
 // pinMode(A10,INPUT);
 pinMode(A12,INPUT);
  pinMode(A14,INPUT);
  pinMode(A15,INPUT);
  pinMode(A13,INPUT);

}

void loop() {
  row12=analogRead(A12);
  row14=analogRead(A14);
  row15=analogRead(A15);
  row13=analogRead(A13);
 //Serial.println(rowA6);
 // Serial.print(" ");

    Serial.print(5222/(row12-13));
  Serial.print(" ");
  Serial.print(5222/(row13-13));
  Serial.print(" ");
  Serial.print(5222/(row14-13));
  Serial.print(" ");
  Serial.print(5222/(row15-13));
  Serial.println(" ");
  delay(200);

}
