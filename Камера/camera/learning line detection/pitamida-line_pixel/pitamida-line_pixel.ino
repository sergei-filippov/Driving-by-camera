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
/*int roundaboutX = 64;
  int roundaboutY = 18;*/
int ccx = 64;
int R = 30;
int ccy = 48;
int de = 68;
int ds = 60;
int startLine = 0;
//double ytest = 0;


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
  tv.capture();

  // uncomment if tracking dark objects
  //tv.fill(INVERT);

  // compute bounding box
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  boolean found = 0;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      c = tv.get_pixel(x, y);
      if (c == 1) {
        found = true;
        if (x < minX) {
          minX = x;
        }
        if (x > maxX) {
          maxX = x;
        }
        if (y < minY) {
          minY = y;
        }
        if (y > maxY) {
          maxY = y;
        }
      }
    }
  }

  // draw bounding box
  tv.fill(0);
  if (1) {
    //   tv.draw_line(64, 48, roundaboutX++, abs(30^2- roundaboutX^2),1);
    /*    tv.draw_line(minX, minY, maxX, minY, 1);
        tv.draw_line(minX, minY, minX, maxY, 1);
        tv.draw_line(maxX, minY, maxX, maxY, 1);
        tv.draw_line(minX, maxY, maxX, maxY, 1);
      //   tv.draw_column(46,51,59,1);
      //   tv.draw_row(59,50,85,1);
      tv.draw_rect(10,10,107,76,2);
        //tv.draw_circle(((maxX + minX) / 2), ((maxY + minY) / 2), 4,1);
        tv.set_pixel(((maxX + minX) / 2), ((maxY + minY) / 2), 1); // also a dot
        //tv.draw_line(((maxX + minX) / 2), ((maxY + minY)/2), ((maxX + minX) / 2),((maxY + minY)/2), 1);  // dot in the centre*/
    tv.draw_line(0, 0, 0, 96, 1);       // drowing a rectangle
    tv.draw_line(0, 95, 128, 95, 1);
    tv.draw_line(127, 94, 127, 0, 1);
    tv.draw_line(127, 0, 0, 0, 1);
    //    sprintf(s, "%d, %d", ((maxX + minX) / 2), ((maxY + minY) / 2));
    //   tv.print(0, 0, s);
  }
  //(64,48) centre of circle
  // tv.draw_line(ccx, ccy,ccx, ccy);
  /*    tv.set_pixel(ccx, abs(R^2 - ccx^2),1);
      ccx = ccx+1;
      Serial.println(ccx);
  */
   for (int i = 0; i < 95; i++) {
  for (int i2 = ds; i2 < de; i2++) {
   
      
      tv.set_pixel(i2, i, 1);
      //  ytest = i*i;
      //  ytest  = abs (70*70 - i*i);
      //   tv.set_pixel(i+64, ytest/30, 1);
      // Serial.println(ytest);
      //
    }
    if(i%2 == 0){
    de++;
    ds--;
    }
  }
de = 68;
ds = 60;

  

  tv.resume();
  tv.delay(1000);
}

