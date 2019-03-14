#include <pollserial.h>

#include <TVout.h>
#include <fontALL.h>
#define W 128
#define H 96

TVout tv;
pollserial pserial;

int num_line = 48;
int now,next;
int count = 0;
int pixel[128], changes[128],widths[23];




void setup()  {
  
  Serial3.begin(9600);
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
 
  boolean found = 0;
  
  for(int i = 0;i <127;i++){
  now = tv.get_pixel(i,num_line);
  next = tv.get_pixel(i+1,num_line);
  if(now!=next){
    changes[count] = next;
    count++;
    if(next > now){
      widths[count] = next-now;
    }else{
      widths[count] = now-next;
    }
  }
  
}
  
  if (found) {
    for(int i = 0;i<23;i++){
      pserial.println(widths[i]);
    }
  }
    tv.draw_line(0, 0, 0, 95, 1);       // drawing a rectangle
    tv.draw_line(0, 95, 127, 95, 1);
    tv.draw_line(127, 95, 127, 0, 1);
    tv.draw_line(127, 0, 0, 0, 1);

    tv.resume();
    tv.delay_frame(5);
  }
