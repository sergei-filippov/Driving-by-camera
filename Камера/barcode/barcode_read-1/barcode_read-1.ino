#include <pollserial.h>

#include <TVout.h>
#include <fontALL.h>
#define W 128
#define H 96

TVout tv;
pollserial pserial;

int num_line = 48;
int now, next;
int count_lines = 0;
int widths[35];
int bline_start = 0;
int bline_end = 0;



void setup()  {


  pserial.begin(9600);
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

  // compute bounding box


 count_lines=0;
  for (int i = 0; i < 127; i++) {
    now = tv.get_pixel(i, num_line);
    next = tv.get_pixel(i + 1, num_line);
    if (next != now) {
      if (next > now) {
        bline_start = i + 1;
      } else {
        bline_end = i;
        widths[count_lines] =(bline_end - bline_start)+1;
        count_lines++;

      }
    }

  }
 

 tv.fill(0);
  for (int i = 0; i < count_lines; i++) {
    pserial.print(widths[i]);
    pserial.print(" ");
  }
   pserial.println();
  tv.draw_line(0,48,128,48,1);
  tv.draw_line(0, 0, 0, 95, 1);       // drawing a rectangle
  tv.draw_line(0, 95, 127, 95, 1);
  tv.draw_line(127, 95, 127, 0, 1);
  tv.draw_line(127, 0, 0, 0, 1);

  tv.resume();
  tv.delay_frame(5);
  pserial.println(count_lines);
}
