#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window

TVout tv;
pollserial pserial;  //instead of Serial

bool debug = 1;  // for debug
bool c;  // value of the current pixel

unsigned char x, y;
bool linestart = 0;
bool line1 = 0, line2 = 0, line3 = 0;
unsigned char linew[H], xstart = W - 1, xend = W - 1, linew1;
unsigned char xstartm[H], xendm[H] /* m for our line (main) */ ,xstart1[H], xend1[H], xstart2[H], xend2[H],xmiddle[H];



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


  for (y = 0; y <H;y+=20) {
    for (x = 0; x < W; x += 2) {
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
      xstart1[y] = xstart1[y - 2]; // odd
      xend1[y] = xend1[y - 2];
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


  if (debug) {
    /*  pserial.print(xstart);
       pserial.print(" ");
       pserial.println(xend);*/
    for (y = 0; y < H ; y += 20) {
    //  pserial.println(xstart1[y]);

      if ( xstart2[y] != W) {
        xstartm[y] = xstart2[y];
        xendm[y] = xend2[y];
        tv.draw_line(xstartm[y], y, xendm[y], y , 1);
      } else {
        xstartm[y] = xstart1[y];
        xendm[y] = xend1[y];
        tv.draw_line(xstartm[y], y, xendm[y], y , 1);
      }
      if(y>=20){
      tv.draw_line(W/2, H, (xendm[y]+xstartm[y])/2, y, 1); 
      }
      xstart1[y] =  W ; // set to zero to avoid influencing on other lines
      xend1[y] = W ;
      xstart2[y] =  W ;
      xend2[y] = W ;
     
    }

   // pserial.println("STOP");


    //  pserial.println(linew1);
    //  tv.print(5, 5, xend[50]);
    tv.draw_line(0, 0, 0, H - 1, 1);     // drawing a rectangle
    tv.draw_line(0, H - 1, W - 1, H - 1, 1);
    tv.draw_line(W - 1, H - 1, W - 1, 0, 1);
    tv.draw_line(W - 1, 0, 0, 0, 1);

    // tv.draw_line(0, y, 128, y, 1);
    //  tv.draw_line(44, 0, 44, H, 1);
    //  tv.draw_line(84, 0, 84, H, 1);
  }

  tv.resume();
  // tv.delay(1000);
  tv.delay_frame(2);

}
