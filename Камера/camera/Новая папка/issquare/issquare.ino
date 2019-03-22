#include <TVout.h>
#include <fontALL.h>
#define W 128
#define H 96

TVout tv;


void setup()  {
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
  tv.fill(INVERT);

  //part 1-4 -- find 4 vertexes black px  // top\left\bottom\right
  //part 1 - top
  bool isfound=0;
  int xv[4];
  int yv[4];
  int ynow=0,xnow=0;  // sort of a buffer 

  for(int y=0;y<H;y++){
    for(int x =0;x<W;x++){
      bool c=0;
      c = tv.get_pixel(x,y);
      if(c){
        isfound=1;
        xv[0]=x;
        yv[0]=y;
      }
      if(isfound) break;
    }
    if(isfound) break;
  }

  // part 2 - left
  xnow=xv[0];
  while(true){
    int amount_inrow=0;               //row=column
    for(int y=yv[0];y<H;y++){               // from y_top to the end
      bool c = tv.get_pixel(xnow,y);
      if(c) amount_inrow++;              // how many black px
      ynow=y;                             // if not alone then edge bottom btw //not good but ok
    }
    if(amount_inrow==0){xnow++; break;}     //if end of figure it means that previous column was edge column
    else{amount_inrow=0; xnow--;}                 //else keep scanning all frame to left

    // tv.resume() // what will happen with capture_array? // would be helpful for debug
  }
  xv[1]=xnow;
  yv[1]=ynow;

  // part 3 - right
  xnow=xv[0];
  while(true){
    int amount_inrow=0;               //row=column
    for(int y=yv[0];y<H;y++){             
      bool c = tv.get_pixel(xnow,y);
      if(c) amount_inrow++;              // how many black px
      ynow=y;                             
    }
    if(amount_inrow==0){xnow--; break;}     
    else{amount_inrow=0; xnow++;}                 

   
  }
  xv[2]=xnow;
  yv[2]=ynow;


  // part 4 - bottom
  ynow=max(yv[1],yv[2]);   // start from the most bottom row
  while(true){
    int amount_inrow=0;               //row
    for(int x=xv[1];x<=xv[2];x++){               
      bool c = tv.get_pixel(x,ynow);
      if(c) amount_inrow++;              // how many black px
      xnow=x;                             
    }
    if(amount_inrow==0){ynow--; break;}     
    else{amount_inrow=0; ynow++;}                 //else keep scanning frame
  }

  xv[3]=xnow;
  yv[3]=ynow;
  


  
  tv.resume();
  tv.delay_frame(2);
}