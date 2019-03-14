#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>  //fonts

#define W 128       // width of the window
#define H 96         // height of the window


// digit pot
#define UD  24                          // выходы к которым подключен модуль
#define INC 23
#define CS  22
//
TVout tv;
pollserial pserial;  //instead of Serial

int digitpot_pos=0;  
bool digitpot_direct=0; // 0 -down // 1-up


void setup()  {
  
  //digit pot
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH); 
  to_down();
  //to_upx(25);                
  //

  pserial.begin(115200);  //transmit angle to mega
  
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





void loop() {
  

  
  tv.capture();
  //tv.fill(0);
  tv.fill(INVERT);       // if tracking dark objects
  

  if(digitpot_direct){
      up();
      digitpot_pos++;
    }
    else{ 
      down();
      digitpot_pos--;
    }
    if(digitpot_pos>100 || digitpot_pos<0){
      digitpot_direct=!digitpot_direct;
    }
  
  
  pserial.print(digitpot_pos);
  pserial.print(" ");
  pserial.println(digitpot_direct);
 

  tv.resume();
  //tv.delay(500);
  tv.delay_frame(30);

}
