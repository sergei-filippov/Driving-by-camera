int d, left,right, centre; // расстояние и значения с датчика
void setup() {
  Serial.begin(9600);
 // pinMode(A10,INPUT);
 pinMode(A12,INPUT);
  pinMode(A14,INPUT);
  pinMode(A15,INPUT);
  pinMode(A13,INPUT);

}

void loop() {
  right =analogRead(A6);
  centre=analogRead(A7);
  left=analogRead(A8);
 // row13=analogRead(A13);
 //Serial.println(rowA6);
 // Serial.print(" ");

    Serial.print(5222/(right-13));
  Serial.print(" ");
  Serial.print(5222/(centre-13));
  Serial.print(" ");
  Serial.print(5222/(left-13));
 // Serial.print(" ");
//  Serial.print(5222/(row15-13));
  Serial.println(" ");
  delay(200);

}
