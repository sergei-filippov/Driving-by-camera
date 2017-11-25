#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window

TVout tv;
pollserial pserial;  //instead of Serial

bool debug = 1;  // for debug
bool c;  // value of the current pixel
bool islinestarted = 0;
bool isstopline;
unsigned char midx = W / 2;
unsigned char midx60, midx30;
unsigned char d = 30;  // segment of calc  // d+line_width+d;

unsigned char firstx = midx - d;
unsigned char lastx = midx + d;


unsigned char z = 0; // counter for any usage
unsigned char x, y;
unsigned char numofobj = 0; // general number of lines or objects
unsigned char xline[10]; // positions of all first and last xs // first is odd and last is even // here only 5 objects

unsigned char widthH, width60, width30;

char angle, angleHto60, angleHto30;
float cosHto60, cosHto30;

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

  // if tracking dark objects
  tv.fill(INVERT);


  /*  y = 30;                       // num of line                         // full calc of line
    for (int x = 0; x < W; x++) {
      c = tv.get_pixel(x, y);
      if (c == 1) {               // if black
        xline[z] = x;
        z++;
        islinestarted = 1;
      }
      if (islinestarted && !c) {
        xline[z] = x;
        z++;
        islinestarted = 0;
      }
    }
  */
  //----------------------------------------------------------//
  y = H;

  for (x = firstx ; x < lastx; x++) {
    c = tv.get_pixel(x, y);
    if (c) {
      firstx = x - d;
      islinestarted = 1;
    }
    if (islinestarted && !c) {
      lastx = x + d;
      islinestarted = 0;
      break;
    }
  }

  //----------------------------------------------------------//
  y = 60;

  for (x = firstx ; x < lastx; x++) {
    c = tv.get_pixel(x, y);
    if (c) {
      firstx = x;
      islinestarted = 1;
    }
    if (islinestarted && !c) {
      lastx = x;
      islinestarted = 0;
      break;
    }
  }

  midx60 = (lastx + firstx) / 2;          // middle of the line
  width60 = (lastx - d) - (firstx + d)
            //------------------------------------------------------------//
            y = 30;

  for (x = firstx ; x < lastx; x++) {
    c = tv.get_pixel(x, y);
    if (c) {
      firstx = x;
      islinestarted = 1;
    }
    if (islinestarted && !c) {
      lastx = x;
      islinestarted = 0;
      break;
    }
  }
  midx30 = (lastx + firstx) / 2;          // middle of the line
  width30 = (lastx - d) - (firstx + d);



  if (width30 > ? && width60 < H - 10 ) { // what is normal?
    isstopline = 1;
  }


  cosHto60 = float(36)) / sqrt(((midx - midx60) * (midx - midx60)) + (36 * 36)); // 36 is H(96) - 60
  cosHto30 = float(66)) / sqrt(((midx - midx30) * (midx - midx30)) + (66 * 66)); // 66 is H(96) - 30

  angleHto60 = acos(cosHto60) * 57.2956;
  angleHto30 = acos(cosHto30) * 57.2956;
  angle = (angleHto60 + angleHto30) / 2;
  if (midx60 > midx) {
  angle *= -1;

}
Serial3.write(angle);  // angle to mega

if (debug) {
  tv.print(5, 5, angle);
    tv.draw_line(0, 0, 0, H, 1);       // drowing a rectangle
    tv.draw_line(0, H, W, H, 1);
    tv.draw_line(W, H, W, 0, 1);
    tv.draw_line(W, 0, 0, 0, 1);

    tv.draw_line(midx, H, midx60, 60, 1);
    tv.draw_line(midx, H, midx30, 30, 1);
  }

  tv.resume();
  tv.delay_frame(5);

}
