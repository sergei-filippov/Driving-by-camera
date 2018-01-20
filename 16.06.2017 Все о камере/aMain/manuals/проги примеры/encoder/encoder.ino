void num_all(int n) {
  switch (n) {

    case 0: num0(); break;
    case 1: num1(); break;
    case 2: num2(); break;
    case 3: num3(); break;
    case 4: num4(); break;
    case 5: num5(); break;
    case 6: num6(); break;
    case 7: num7(); break;
    case 8: num8(); break;
    case 9: num9(); break;
    }
}
void num0()
{
  digitalWrite(6, LOW); digitalWrite(7, LOW);
  digitalWrite(8, LOW); digitalWrite(9, LOW);
  digitalWrite(10, LOW); digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
}
void num1()
{
  num3();
  digitalWrite(6, HIGH); digitalWrite(9, HIGH); digitalWrite(12, HIGH);
}

void num2()
{
  num8();
  digitalWrite(8, HIGH); digitalWrite(11, HIGH);
}

void num3()
{
  num8();
  digitalWrite(10, HIGH); digitalWrite(11, HIGH);
}

void num4()
{
  num9();
  digitalWrite(6, HIGH); digitalWrite(10, HIGH); digitalWrite(9, HIGH);
}

void num5()
{
  num8();
  digitalWrite(10, HIGH); digitalWrite(7, HIGH);
}

void num6()
{
  num8();
  digitalWrite(6, HIGH); digitalWrite(7, HIGH);
}

void num7()
{
  num1();
  digitalWrite(6, LOW);
}

void num8()
{
  num0();
  digitalWrite(12, LOW);
}

void num9()
{
  num8();
  digitalWrite(10, HIGH);
}
int pwm_encoder(int pwmstart) {

  int encoder_pwm = pwmstart, pwm01, pwm10,t1,t2;
  t1 = millis();
  
  while (t2-t1 < 30000) {
    t2 = millis();
    if (digitalRead(3) == 0) {
      while (digitalRead(3) == 0) {
        if (digitalRead(2) == 0) {
          encoder_pwm--;
          break;
        }
      }
    }
    delay(5);
    if (digitalRead(2) == 0) {
      while (digitalRead(2) == 0) {
        if (digitalRead(3) == 0) {
          encoder_pwm++;
          break;
        }
      }
    }
    delay(5);
    pwm10 = encoder_pwm / 10;
    pwm01 = encoder_pwm % 10;
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    num_all(pwm01);
    delay(10);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    num_all(pwm10);
  }
  //Serial.println(encoder_pwm);
  return (encoder_pwm);
}


void setup()
{

  Serial.begin(9600);
  pinMode(2, INPUT); pinMode(3, INPUT); // encoder               // pins 2-12 are reserved

  pinMode(6, OUTPUT); pinMode(7, OUTPUT);
  pinMode(8, OUTPUT); pinMode(9, OUTPUT);
  pinMode(10, OUTPUT); pinMode(11, OUTPUT);
  pinMode(12, OUTPUT); pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}
int a, speed1 = 70;
void loop()
{
  a=pwm_encoder(speed1);
Serial.println(a);
}
