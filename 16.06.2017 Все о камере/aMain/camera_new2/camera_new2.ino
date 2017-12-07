#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window

TVout tv;
pollserial pserial;  //instead of Serial

bool debug = 1;  // for debug
bool c;  // value of the current pixel

int x, y;


void setup()  {

  if (debug) {
    pserial.begin(9600);
  }

  //Serial3.begin(9600);  //angle to mega

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
 
  // if tracking dark objects
  tv.fill(INVERT);
/*
   bool linestart;
  int xstart,xend,linew;
y=50;
  for(x=44; x<85;x++){
    c = get_pixel(x,y);                                   to find the width of line
    if(c && !linestart){
      linestart=1;
      xstart = x;
    }else if(!c && linestart){
      linestart =0;
      xend = x;
      break;
    }
  }
  linew = xend-xstart;
*/


//----------------------------// to find a distance */

//найти коэффициент для перевода из количества пискелей до обьекта (вертикально от камеры(нижней средней)) в см.



//--------------------------//

//----------------------------------// 

  tv.fill(0);
  if (debug) {
    // tv.print(5, 5, lastx);
    tv.draw_line(0, 0, 0, H - 1, 1);     // drawing a rectangle
    tv.draw_line(0, H - 1, W - 1, H - 1, 1);
    tv.draw_line(W - 1, H - 1, W - 1, 0, 1);
    tv.draw_line(W - 1, 0, 0, 0, 1);
  }

  tv.resume();
  tv.delay_frame(2);

}
