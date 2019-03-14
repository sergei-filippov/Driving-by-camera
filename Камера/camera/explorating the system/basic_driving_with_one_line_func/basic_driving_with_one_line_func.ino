#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window
#define debugbutton 22   // connect with gnd

TVout tv;
pollserial pserial;  //instead of Serial



bool debug=0;

void setup()  {
  
  // pinMode(debugbutton, INPUT_PULLUP);
  pinMode(debugbutton, INPUT);         //button swithes on debug mode // debug mode dislplays overlay and enables connection to PC
  digitalWrite(debugbutton, HIGH);

  /*if (digitalRead(debugbutton) == 1) {
    debug = 0;
  }*/

  if (debug) {
    pserial.begin(115200);    
  }
  
 Serial2.begin(115200);  //transmit angle to mega

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


double get_angle(int y){
  
  tv.fill(INVERT);       // if tracking dark objects
  
   
  int xstart=0, xend=H, midx;
  double tgangleOneLine, angleOneLine;  // tg of the angle
  bool islinestart=0;
  bool iscrossing=0;

    
  for (int x = 0; x < W; x += 1) {
    bool c = tv.get_pixel(x, y);
    if(c && !islinestart){             // calculate the begining and the end of the line in onw row
      xstart = x;
      islinestart=1;

      //pserial.print( xstart);pserial.print(" "); pserial.print(xend); pserial.println();
    }
      
    if(!c && islinestart){
      xend = x;
      break;
    }
  }
    
  if((xend - xstart) > 70) {   //if crossing  - move forward
    xstart =  0; 
    xend = H;
    iscrossing=1;
  }
    
  midx = ((xend + xstart) / 2);  // middle point in the black segment of line
    
  tgangleOneLine = atan(1.0 * (midx - (W / 2)) / ((H - y) + 90));
  angleOneLine = (tgangleOneLine) * 57.2956;  // real angle

  if(debug){
    tv.fill(0);
    tv.draw_line(xstart, y, xend, y , 1);
    tv.fill(INVERT);
  }

  return angleOneLine;
}

void show_rect(){
  tv.fill(0);
  tv.draw_line(0, 0, 0, H - 1, 1);         // drawing a rectangle
  tv.draw_line(0, H - 1, W - 1, H - 1, 1);
  tv.draw_line(W - 1, H - 1, W - 1, 0, 1);
  tv.draw_line(W - 1, 0, 0, 0, 1);
  tv.fill(INVERT);
}

void loop() {


  const int firstline =90; 
  const int ncountline = 5;      // how many lines we count in one frame 
  int deltaline = H/ncountline;  // distance between lines in the frame which we count 

  double *angles = new double[ncountline];   // array for all angles
  //  double coeffAngle[]= {100,70,50,30,20,10};   // furtherer line - smaller value // in percents
  //int *linew = new int[H];

  tv.capture();
  tv.fill(INVERT);       // if tracking dark objects

  double angleMain=0;
  int position1=0;
  int y=firstline;
  
  for(int i =firstline;i<ncountline;i+=deltaline){
    angles[i]=get_angle(i);
    angleMain+=angles[i];
  }

  angleMain/=ncountline;


  if(debug){
    pserial.println(angleMain);
  }
   
  
  Serial2.write((int)angleMain);  // transmit ot mega
  //-----------------------------------------------------------------------------------//
  //-----------------------------------------------------------------------------------//
  if (debug) {
    tv.fill(0); 
    tv.print(120, 80, angleMain );
    tv.draw_line(xstart, y, xend, y , 1);

  }

  tv.resume();
 //  tv.delay(1000);
  tv.delay_frame(1);

}
