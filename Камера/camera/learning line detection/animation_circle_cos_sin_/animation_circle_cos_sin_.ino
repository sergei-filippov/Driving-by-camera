#include <TVout.h>
#include <video_gen.h>






#include <font4x6.h>
#include <font6x8.h>
#include <font8x8.h>
#include <font8x8ext.h>
#include <fontALL.h>


#define W 128
#define H 96
    
TVout tv;
unsigned char x, y;
unsigned char c;
unsigned char minX, minY, maxX, maxY;
char s[32];

int rotationY = 0;
int counter = 0;
int r2 = 20;
int r = 40;
int Xc2 = 25;
int Yc2 = 25; 
int Xc = W / 2; //64
int Yc = H / 2; //48
float Xt, Yt;
float Xt2, Yt2;
float angle = 0;



void setup()  {
  //  Serial.begin(9600);
  tv.begin(PAL, W, H);
  initOverlay();
  initInputProcessing();

  tv.select_font(font6x8);
  tv.fill(0);
}


void initOverlay() {
  TCCR1A = 0;
  // Enable timer1.  ICES0 is set to 0 for falling edge detection on input capture pin.
  TCCR1B = _BV(CS10);

  // Enable input capture interrupt
  TIMSK1 |= _BV(ICIE1);

  // Enable external interrupt INT0 on pin 2 with falling edge.
  EIMSK = _BV(INT0);
  EICRA = _BV(ISC01);
}

void initInputProcessing() {
  // Analog Comparator setup
  ADCSRA &= ~_BV(ADEN); // disable ADC
  ADCSRB |= _BV(ACME); // enable ADC multiplexer
  ADMUX &= ~_BV(MUX0);  // select A2 for use as AIN1 (negative voltage of comparator)
  ADMUX |= _BV(MUX1);
  ADMUX &= ~_BV(MUX2);
  ACSR &= ~_BV(ACIE);  // disable analog comparator interrupts
  ACSR &= ~_BV(ACIC);  // disable analog comparator input capture
}

// Required
ISR(INT0_vect) {
  display.scanLine = 0;
}


void loop() {
//  tv.capture();

  // uncomment if tracking dark objects
  //tv.fill(INVERT);

  // compute bounding box
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  boolean found = 0;

  // draw bounding box
  //tv.fill(0);  //   нет очистки экрана
  if (1) {

    tv.draw_line(0, 0, 0, 96, 1);       // drowing a big rectangle
    tv.draw_line(0, 95, 128, 95, 1);
    tv.draw_line(127, 94, 127, 0, 1);
    tv.draw_line(127, 0, 0, 0, 1);
    //    sprintf(s, "%d, %d", ((maxX + minX) / 2), ((maxY + minY) / 2));
    //   tv.print(0, 0, s);
  }


//  Xt = 40 * cos(angle * 0.017);
//  Yt = 40 * sin(angle * 0.017);
  Xt = r * cos(angle);
  Yt = r * sin(angle);
   Xt2 = r2 * cos(angle*3);
  Yt2 = r2 * sin(angle*3);
   angle+=0.01;
 // angle += 0.1;
 // if (angle > 90) angle = 0;
  counter++;
  tv.draw_line(Xt2+Xc2, Yt2+Yc2, Xt+Xc, Yt+Yc, 2);
//tv.draw_line(0,0,128,96,0);    // инверсия - изменяет то что было на противоположное
  // rotationY++;

 // tv.print(counter);
  //   tv.print(0, 85, angle);





  tv.resume();
  tv.delay(50);
}

