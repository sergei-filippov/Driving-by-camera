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
int r = 45;
int Xc = W/2; //64
int Yc = H/2;  //48
int Xt, Yt,dy;
int dx = 0;



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
 // tv.capture();

  // uncomment if tracking dark objects
  //tv.fill(INVERT);

  // compute bounding box
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  boolean found = 0;

  // draw bounding box
  tv.fill(0);
  if (1) {

    tv.draw_line(0, 0, 0, 96, 1);       // drowing a big rectangle
    tv.draw_line(0, 95, 128, 95, 1);
    tv.draw_line(127, 94, 127, 0, 1);
    tv.draw_line(127, 0, 0, 0, 1);
    //    sprintf(s, "%d, %d", ((maxX + minX) / 2), ((maxY + minY) / 2));
    //   tv.print(0, 0, s);
  }
 
  
  
  Xt = Xc+r+dx;
  dx--;
  dy = sqrt(r*r-(Xt-Xc)*(Xt-Xc));
  Yt = Yc + dy;
  if(Xt<Xc-r){
    
  }
  tv.fill(0 );
  tv.draw_line(W/2, H/2, Xt, Yt, 2);
  
  counter++;
  // rotationY++;

  tv.print(counter);




  tv.resume();
  tv.delay(200);
}

