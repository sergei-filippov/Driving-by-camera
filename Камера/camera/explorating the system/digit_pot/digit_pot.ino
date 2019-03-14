#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window
#define debugbutton 25   // connect with gnd

// digit pot
#define UD  24                          // выходы к которым подключен модуль
#define INC 23
#define CS  22
//
TVout tv;
pollserial pserial;  //instead of Serial

int digitpot_pos=0;  
bool digitpot_direct=0; // 0 -down // 1-up

bool debug=1;

void setup()  {
  
  //digit pot
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH); 
  to_down();
  to_upx(50);                
  //

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

void to_down(){
  for(int i=0;i<100;i++){
    down();
  }
  digitpot_direct=1;
  digitpot_pos=0;
}


void to_upx(int x){
  for(int i=0;i<x;i++){
    up();
  }
  digitpot_direct=0; //
  digitpot_pos=x;
}

void up(){                            // поднимает ползунок в верх на 1 ступень
  digitalWrite(UD, HIGH);             // на U/D подаем единицу
  digitalWrite(INC, HIGH);            // и на INC тоже
  digitalWrite(CS, LOW);              // включаем микросхему
  delayMicroseconds(1);               // ждем
  digitalWrite(INC, LOW);             // дергаем вход INC
  delayMicroseconds(1);
  digitalWrite(INC, HIGH);
  delayMicroseconds(1);
  digitalWrite(INC, LOW);                  // в этом случаи положение ползунка записано не будет
  digitalWrite(CS, HIGH);             // выключаем микросхему и записываем положение в EEPROM 
}

void down(){                          // опускаем ползунок в верх на 1 ступень
  digitalWrite(UD, LOW);
  digitalWrite(INC, HIGH);
  digitalWrite(CS, LOW);
  delayMicroseconds(1);
  digitalWrite(INC, LOW);
  delayMicroseconds(1);
  digitalWrite(INC, HIGH);
  delayMicroseconds(1);
  digitalWrite(INC, LOW);                  // в этом случаи положение ползунка записано не будет
  digitalWrite(CS, HIGH);
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


double get_angle(int y){    // c : white-1, black-0
  
  //tv.fill(INVERT);       // if tracking dark objects
  
  //pserial.println(y);

  int xstart=W, xend=0, midx;
  double tgangleOneLine, angleOneLine;  // tg of the angle
  bool islinestart=0;
  bool iscrossing=0;

    
  for (int x = 0; x < W; x++) {
    int c = tv.get_pixel(x, y);
    //c=!c;             
    pserial.print(c);                 // c was white-1, black-0 and after the action vice versa
    if(c && !islinestart){             // calculate the begining and the end of the line in onw row
      xstart = x;
      islinestart=1;

/*      pserial.print("xstart: ");
      pserial.print(xstart);
      pserial.print("   .xend: ");
      pserial.println(xend);
*/
      //pserial.print( xstart);pserial.print(" "); pserial.print(xend); pserial.println();
    }
        
    if(!c && islinestart){
      xend = x;
      break;
    }
  }
    
    pserial.println();


  if((xend - xstart) > 70) {   //if crossing  - move forward
    xstart =  0; 
    xend = H;
    iscrossing=1;
  }
   
/*  pserial.print(xstart);
  pserial.print(" ");
  pserial.println(xend);
*/

  midx = ((xend + xstart) / 2);  // middle point in the black segment of line
    
  tgangleOneLine = atan(1.0 * (midx - (W / 2)) / ((H - y) + 90));
  angleOneLine = (tgangleOneLine) * 57.2956;  // real angle

  if(debug){
    //tv.fill(0);
    tv.draw_line(xstart, y, xend, y , 1);
    //tv.fill(INVERT);
  }

  return angleOneLine;
}

void show_rect(){
  //tv.fill(0);
  tv.draw_line(0, 0, 0, H - 1, 1);         // drawing a rectangle
  tv.draw_line(0, H - 1, W - 1, H - 1, 1);
  tv.draw_line(W - 1, H - 1, W - 1, 0, 1);
  tv.draw_line(W - 1, 0, 0, 0, 1);
  //tv.fill(INVERT);
}

void loop() {
  

  const int firstline =50;   // first from the bottom // closest to the camera 
  const int ncountline = 1;      // how many lines we count in one frame 
  int deltaline = H/ncountline;  // distance between lines in the frame which we count 

  double *angles = new double[ncountline];   // array for all angles
  //  double coeffAngle[]= {100,70,50,30,20,10};   // furtherer line - smaller value // in percents
  //int *linew = new int[H];

  tv.capture();
  tv.fill(0);
  //tv.fill(INVERT);       // if tracking dark objects

  double angleMain=0;
  int position1=0;
  int y=firstline;
  
  /*
  pserial.print(ncountline);
  pserial.print(" ");
  pserial.println(deltaline);
  */

  //pserial.println(firstline);

  for(int i =firstline;i>=0;i-=deltaline){
    angles[i]=get_angle(i);
    angleMain+=angles[i];

   // pserial.println(angles[i]);
  }
  //pserial.println("");

  angleMain/=ncountline;


  if(debug){
    //pserial.println(angleMain);
  }
   
  
  Serial2.write((int)angleMain);  // transmit ot mega
  //-----------------------------------------------------------------------------------//
  //-----------------------------------------------------------------------------------//
  //tv.fill(0); 
  if (debug) {
    
    tv.print(120, 80, angleMain );
    show_rect();

  }


  tv.resume();

  //tv.delay(500);
  tv.delay_frame(5);
  //tv.fill(0);

}
