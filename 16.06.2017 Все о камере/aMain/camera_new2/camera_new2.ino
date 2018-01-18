#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window
#define debugbutton 22

TVout tv;
pollserial pserial;  //instead of Serial

bool debug = 1;  // for debug
unsigned char ncountline = 1;


bool c;  // value of the current pixel
unsigned char x, y;
bool linestart = 0;
bool line1 = 0, line2 = 0, line3 = 0;
unsigned char linew[H], xstart = W - 1, xend = W - 1, linew1; /* m is for main*/;
unsigned char xstartm[H], xendm[H] /* m for our line (main) */ , xstart1[H], xend1[H], xstart2[H], xend2[H], xmiddle[H];
double tgangle[H], angle[H], anglem = 0.0;
int anglemi, lineofcount = 50, countangles, preangles[5], averageangle;


void setup()  {
  pinMode(debugbutton, INPUT);

  if (digitalRead(debugbutton) == 1) {
    debug = 0;
  }
  if (debug) {
    pserial.begin(9600);
  }

  for (int i = 0; i < 5; i++) {
    preangles[i] = 0;
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


  for (y = 0; y < H; y += 10) {
    for (x = 0; x < W; x += 1) {
      c = tv.get_pixel(x, y);
      if (c && !linestart && !line1) {
        linestart = 1;
        xstart = x;
        xstart1[y] = xstart;

      } else if (!c && linestart && !line1) {
        linestart = 0;
        xend = x - 2;



        xend1[y] = xend;
        line1 = 1;


      } else if (c && !linestart && line1) {
        linestart = 1;
        xstart = x;

      } else if (!c && linestart && line1) {
        linestart = 0;
        xend = x - 2;
        xstart2[y] = xstart;
        xend2[y] = xend;
      }
    }

    if ((xend - xstart) > 70) {   //if crossing
      xstart1[y] =  0; // odd
      xend1[y] = H - 1;
    }


    // linew[y] = xend1 - xstart1;
    line1 = 0;          // set to zero to avoid influencing on other lines
    linestart = 0;
    xend = W ;
    xstart = W ;

  }


  //----------------------------// to find a distance */

  //найти коэффициент для перевода из количества пискелей до обьекта (вертикально от камеры(нижней средней)) в см.



  //--------------------------//

  //----------------------------------//

  tv.fill(0);

  for (y = lineofcount; y < H ; y += 66) {
    if ( xstart2[y] != W) {
      xstartm[y] = xstart2[y];
      xendm[y] = xend2[y];
    } else {
      xstartm[y] = xstart1[y];
      xendm[y] = xend1[y];
    }

    /* if (y >= 20) {
       tv.draw_line(W / 2, H, (xendm[y] + xstartm[y]) / 2, y, 1);
      }*/

    tgangle[y] = atan(1.0 * (((xendm[y] + xstartm[y]) / 2) - (W / 2)) / ((H - y) + 90));
    angle[y] = (tgangle[y]) * 57.2956;
    anglem += angle[y];
  }
  anglem = anglem / (ncountline); // how many lines do we count
  anglemi = anglem;

  // Serial3.write(anglemi);

  if (countangles == 5) {
    countangles = 0;
  }
  preangles[countangles] = anglemi;
  countangles += 1;
  for (int i = 0; i < 5; i++) {
    averageangle += preangles[i];
  }
  averageangle /= 5;
  Serial3.write(anglemi);
  
  //-----------------------------------------------------------------------------------//
  //-----------------------------------------------------------------------------------//
  if (debug) {

    for (y = lineofcount; y < H ; y += 66) {
      tv.draw_line(xstartm[y], y, xendm[y], y , 1);
      tv.draw_line(W / 2, H + 90, (xendm[y] + xstartm[y]) / 2, y, 1);
    }

    pserial.print(anglemi);
    // pserial.println("STOP");
    tv.print(5, 5, averageangle);

    tv.draw_line(0, 0, 0, H - 1, 1);     // drawing a rectangle
    tv.draw_line(0, H - 1, W - 1, H - 1, 1);
    tv.draw_line(W - 1, H - 1, W - 1, 0, 1);
    tv.draw_line(W - 1, 0, 0, 0, 1);
  }
  for (y = lineofcount; y < H ; y += 66) {
    xstart1[y] =  W ; // set to zero to avoid influencing on other lines
    xend1[y] = W ;
    xstart2[y] =  W ;
    xend2[y] = W ;
    xstartm[y] =  W ;
    xendm[y] = W ;
  }
  anglem = 0;
  averageangle = 0;
  tv.resume();
  // tv.delay(1000);
  tv.delay_frame(1);

}
