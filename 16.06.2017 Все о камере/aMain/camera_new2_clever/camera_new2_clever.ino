#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window
#define debugbutton 22   // connect with gnd

TVout tv;
pollserial pserial;  //instead of Serial

bool debug = 1;  // for debug

  int ncountline = 5;  // how many lines we count in one frame 
  int deltaline = H/ncountline;  // distance between lines in the frame which we count 

  double *angles = new double[ncountline];   // array for all angles
  int *coeffAngle  = new int [ncountline]; //= {100,70,50,30,20,10};   // furtherer line - smaller value // in percents


int firstline =1; // first line from top we count 


bool c;  // value of the current pixel
unsigned char x, y;       
unsigned char linew[H], xstart = W - 1, xend = 0; 
double tgangleOneLine;  // tg of the angle
double angleOneLine, angleMain;


int position1=0; // for the array of angles


int xshift = 0;  // amount of px to shift middle of the line to reduce the angle
int midx = 0; //(xendm[y] + xstartm[y]) / 2)

void setup()  {
  
  // pinMode(debugbutton, INPUT_PULLUP);
  pinMode(debugbutton, INPUT);
  digitalWrite(debugbutton, HIGH);

  /*if (digitalRead(debugbutton) == 1) {
    debug = 0;
  }*/
  if (debug) {
    pserial.begin(115200);
  }
  

  

  Serial3.begin(115200);  //angle to mega

  tv.begin(PAL, W, H);
  initOverlay();
  initInputProcessing();
  tv.select_font(font8x8);
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

  for (y = firstline; y < H; y += deltaline) {
    bool islinestart=0;
    bool iscrossing=0;
    for (x = 0; x < W; x += 1) {
      c = tv.get_pixel(x, y);
      
      if(c && !islinestart){
        xstart = x;
      }
      if(!c && islinestart){
        xend = x;
      }
    }
    
    if ((xend - xstart) > 70) {   //if crossing
      xstart =  0; 
      xend = H;
      iscrossing=1;
    }


  //----------------------------// to find a distance */

  //найти коэффициент для перевода из количества пискелей до обьекта (вертикально от камеры(нижней средней)) в см.



  //--------------------------//

  //----------------------------------//

  
    //-------*-----------------------------------------------//
 
    midx = ((xend + xstart) / 2);  // middle point in the black segment of line
    tgangleOneLine = atan(1.0 * (midx - (W / 2)) / ((H - y) + 90));
    angleOneLine = (tgangleOneLine) * 57.2956;  // real angle
    angles[position1] = angleOneLine * coeffAngle[position1];  // changed angle
    position1++;
    
    tv.fill(0);  // to draw
    if(debug){
      tv.draw_line(xstart, y, xend, y , 1);
    }
    tv.fill(INVERT); // to get
  }
  
  for(int i = 0;i<ncountline;i++){
    angleMain+=angles[i];
  }
  angleMain /= ncountline; // how many lines do we count

   if(debug){
      pserial.println(angleMain);
   }
   
   tv.fill(0);
  Serial3.write((int)angleMain);  // transmit ot mega
  //-----------------------------------------------------------------------------------//
  //-----------------------------------------------------------------------------------//
  if (debug) {
    // pserial.println("STOP");
    tv.print(120, 80, angleMain );

    tv.draw_line(0, 0, 0, H - 1, 1);         // drawing a rectangle
    tv.draw_line(0, H - 1, W - 1, H - 1, 1);
    tv.draw_line(W - 1, H - 1, W - 1, 0, 1);
    tv.draw_line(W - 1, 0, 0, 0, 1);
  }

 
  tv.resume();
  // tv.delay(1000);
  tv.delay_frame(1);

}
