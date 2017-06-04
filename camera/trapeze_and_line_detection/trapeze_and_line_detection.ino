#include <TVout.h>
#include <fontALL.h>
#define W 128
#define H 96

TVout tv;
unsigned char x, y;
unsigned char c;
unsigned char minX, minY, maxX, maxY, uxmid, dxmid;
float xmidmin;
float xmid;
float xmidmax;
unsigned char xu = 70;
char s[32];
byte midX[96];



void setup()  {
  tv.begin(PAL, W, H);
  initOverlay();
  initInputProcessing();

  tv.select_font(font4x6);
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
  tv.fill(INVERT);
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  boolean found = 0;
  for (int y = 20; y < H; y += 75) {
    minX = W;
    maxX = 0;
    for (int x = 70; x < W; x++) {
      c = tv.get_pixel(x, y);
      if (c == 1) {
        found = true;
        if (x < minX) {
          minX = x;
        }
        if (x > maxX) {
          maxX = x;
        }
      }
    }
    midX[y] = int((minX + maxX) / 2);
  }
  uxmid = midX[0];
  dxmid = midX[96];
  xmid = 20.0 / 76;     //76 строк  и 20



  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  found = 0;
  for (int y = 10; y < H; y++) {
    minX = W;
    maxX = 0;
    xmidmax = uxmid + 20;
    xmidmin = uxmid - 20;
    xmidmin -= xmid;
    xmidmax += xmid;
    for (int x = xmidmin ; x <=  xmidmax; x++) {
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
    midX[y] = int((minX + maxX) / 2);
  }

  // draw bounding box
  tv.fill(0);
  if (found) {
    for (int y = minY; y <= maxY; y++) {
      tv.set_pixel(midX[y] - 3, y, 1);
    }

    tv.draw_line((maxX + minX) / 2 - 3, maxY, (maxX + minX) / 2 - 3, minY, 1); //vertical line

    /*  tv.draw_line(minX, minY, maxX, minY, 1);
        tv.draw_line(minX, minY, minX, maxY, 1);
        tv.draw_line(maxX, minY, maxX, maxY, 1);
        tv.draw_line(minX, maxY, maxX, maxY, 1);*/

    // sprintf(s, "%d, %d", ((maxX + minX) / 2), ((maxY + minY) / 2));
    //tv.print(0, 0, s);
  }
  tv.draw_line(xu, 10, 127 , 10, 1);      // drowing a trapeze
  tv.draw_line(127, 10, 127, 94, 1);
  tv.draw_line(127, 94, xu, 94, 1);
  tv.draw_line(xu, 94, xu, 10, 1);



  tv.draw_line(0, 0, 0, 94, 1);       // drowing a rectangle
  tv.draw_line(0, 94, 127, 95, 1);
  tv.draw_line(127, 94, 127, 0, 1);
  tv.draw_line(127, 0, 0, 0, 1);

  tv.resume();
  tv.delay_frame(2);
}
