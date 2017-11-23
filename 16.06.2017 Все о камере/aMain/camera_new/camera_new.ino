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


 for(int i = 0;i<W;i++){
  
 }
  tv.resume();
  tv.delay_frame(5);

}
