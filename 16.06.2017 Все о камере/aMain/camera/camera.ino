#include <pollserial.h>

#include <TVout.h>
#include <fontALL.h>  //fonts
#define W 128       // width of the window
#define H 96         // height of the window

TVout tv;
pollserial pserial;  //instead of Serial

bool debug = 1;
unsigned char x, y;
unsigned char c;
unsigned char dX, uX, minY, minX, maxX, maxY;   //d-down u - up
int angle;
float cosangle;  // cos of the angle in rad
char s[32];
byte midX[2];
// --------------for 2-nd line detection//
int liner_end;
int num_line = 30;
int now, next;
int count_lines = 0;
int widths[2];
int bline_start = 0;
int bline_end = 0;
//-------------------------//



void setup()  {

  if (debug) {
    pserial.begin(9600);
  }

  Serial3.begin(9600);  //angle to mega

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


  //------------for right line detection
  count_lines = 0;
  for (int i = 0; i < 127; i++) {
    now = tv.get_pixel(i, num_line);
    next = tv.get_pixel(i + 1, num_line);
    if (now != next) {
      if (now < next) {
        bline_start = i + 1;
      } else {
        count_lines++;
        //---------------------лишняя линия
        if (count_lines == 1) {
          liner_end = i;
        }
        //---------------------//
        bline_end = i;
        widths[count_lines] = (bline_end - bline_start) + 1;
      }
    }
  }
  // if there are no unnecessary lines
  if (count_lines == 1) {
    liner_end = 0;
  }

  //-------------------------------------//

  // compute bounding box
  minX = W;
  minY = H;
  maxX = 0;
  maxY = 0;
  boolean found = 0;
  y = 30;    // the tenth row
  for (int x = liner_end + 1; x < W; x++) {
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
  if (maxX < 126 && minX > 2) {
    uX = int((minX + maxX) / 2);
  }

  /*  minX = W;
    maxX = 0;
    y = H - 1;           //!!!!!
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
    if(maxX<126 && minX >2){
      dX = int((minX + maxX) / 2);
    }
  */
  maxY = 96;
  dX = int(W / 2);
  // draw bounding box
  tv.fill(0);
  if (found) {
    //tv.draw_line((maxX+minX)/2-3,maxY,(maxX+minX)/2-3,minY,1);   // vertical line

    if (debug) {
      tv.draw_line(int(W / 2), 0, int(W / 2), H, 1); // screen vertical line


      tv.draw_line(int(W / 2), H, uX, minY, 1); // line between points
    }

    // tv.draw_line((maxX+minX)/2-3,maxY,(maxX+minX)/2-3,minY,1);     //vertical line

    /*  tv.draw_line(minX, minY, maxX, minY, 1);
        tv.draw_line(minX, minY, minX, maxY, 1);
        tv.draw_line(maxX, minY, maxX, maxY, 1);
        tv.draw_line(minX, maxY, maxX, maxY, 1);*/

    // sprintf(s, "%d, %d", ((maxX + minX) / 2), ((maxY + minY) / 2));
    //tv.print(0, 0, s);

    cosangle = (float(H) - minY) / sqrt(((dX - uX) * (dX - uX)) + ((H - minY) * (H - minY))); // скалярное произведение векторов
    //cosangle = sqrt(((float(dX)-uX)*(dX-uX))+((maxY-minY)*(maxY-minY)));

    angle = acos(cosangle) * 57.2956;

    if (uX > dX) {
      angle *= -1;

    }
    Serial3.write(angle);  // angle to mega

    if (debug) {
      tv.print(5, 5, angle );
      pserial.println(count_lines);
      tv.draw_line(0, 0, 0, 95, 1);       // drowing a rectangle
      tv.draw_line(0, 95, 127, 95, 1);
      tv.draw_line(127, 95, 127, 0, 1);
      tv.draw_line(127, 0, 0, 0, 1);
    }

  }
  tv.resume();
  tv.delay_frame(5);

}
