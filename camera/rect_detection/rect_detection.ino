#include <TVout.h>
#include <video_gen.h>

//#include <pollserial.h>


#include <font4x6.h>
#include <font6x8.h>
#include <font8x8.h>
#include <font8x8ext.h>
#include <fontALL.h>




#define W 128
#define H 96
//pollserial pserial;
TVout tv;
unsigned char x, y;
unsigned char c;
unsigned char minX, minY, maxX, maxY;
char s[32];
int xi, yi;


void setup()  {
  tv.begin(PAL, W, H);
  initOverlay();
  initInputProcessing();

  tv.select_font(font4x6);
    tv.fill(0);
  //pserial.begin(250000);
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
  
  
  // compute bounding box
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  boolean found = 0;
  for (int y = 0; y < H; y++) {
    tv.fill(2);
    minX = W;
    maxX = 0;
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
// pserial.println(maxX);
    }
   // pserial.println((maxX + minX) / 2);
    
    tv.set_pixel(int((maxX + minX) / 2), y, 0);
  }

  // draw centre line by pixels

  //  tv.draw_line(0, 0, 128, 96, 1);
  //sprintf(s, "%d, %d", ((maxX + minX) / 2), ((maxY + minY) / 2));
  // tv.print(0, 0, s);


  tv.draw_line(0, 0, 0, 96, 1);       // drowing a rectangle
  tv.draw_line(0, 95, 128, 95, 1);
  tv.draw_line(127, 94, 127, 0, 1);
  tv.draw_line(127, 0, 0, 0, 1);
  tv.resume();
  tv.delay_frame(2);
}
