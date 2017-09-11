#include <math.h>
double deg, degree;
int X1,X2,Y1,Y2;
int x,y,x1,y1,x2,y2,x3,y3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
x=64;
y=96;
x1=64;
y1=92;
x2=64;
y2=96;
x3=61;
y3 =92;
  X2 = x1-x;
  Y2 = y1-y;
  // lineline
  X1 = x3-x2;
  Y1 = y3-y2; 
  Serial.println(X2); 
  Serial.println(Y2);
  Serial.println(X1);
  Serial.println(Y1);
 double deg1 = (Y2*Y1)/(96*sqrt(X1*X1+Y1*Y1));
 deg = (X2*X1+Y2*Y1)/(sqrt(X2*X2+Y2*Y2)*sqrt(X1*X1+Y1*Y1));
 degree = acos(deg)*180/3.14;
 double degree1 = acos(deg1)*180/3.14;
 Serial.println(deg);
 Serial.println(degree);
 Serial.println(deg1);
 Serial.println(degree1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
