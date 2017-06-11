/*
 * Аннотация.
 *   Компьютерное зрение.
 *     Очень хочется писать матом комментарии. Запретили...
 *   Тонны мусорного кода. На ночь читать не советую. Если только вы не учёный, и перед вами не стоит задача свести человека с ума.  
 * День 100 с боооольшим таким гаком. Дедлайн скоро. Код не работает, насяльника ругается(  
 */
//_______________________________________ Подключение библиотек. Инициализация переменных. _____________________________
//_____________________________________________________________________________________________________________________
#include <TVout.h>
#include <fontALL.h>
#define W 128
#define H 96
int x1; //-------- Хренотень, что бы массив Х заполнять. --------
TVout tv;
boolean stp = false;
unsigned char x,y; //--------- Ну если это не понятно - тогда срочно брысь отседова! ------- 
unsigned char c; //----------- Для пикселя. Слегка расистски. Детектор на черного.нечерного. -----
unsigned char minX,minY,maxX,maxY;//-------------- Сами догадаетесь. ---------------------------
unsigned char Xmax,Xmin,Ymax,Ymin;
//int minX,minY,maxX,maxY;
int X1,X2,Y1,Y2;//------------- Переменные для вычисления угла. --------
double deg,degr,degree;
char X[96]; // --------- Массив х-ов черной линии. -------
boolean fs = false; //--------- c firstseen --------------
int last;


//_____________________________________________________ Установка разрешения экрана. Настройка монитора порта. _________________________
//______________________________________________________________________________________________________________________________________
void setup()  
{
  tv.begin(PAL, W, H);
  initOverlay();
  initInputProcessing();

  //tv.select_font(font4x6);
  tv.select_font(font8x8);
  tv.fill(0);
  Serial.begin (115200);
  Serial1.begin(115200);
  pinMode(5, OUTPUT);
}

//_________________________________________________ Системная часть. Настройка оверлея. Трогать не рекомендую. ________________________
//_____________________________________________________________________________________________________________________________________
void initOverlay()
{
  TCCR1A = 0;
  // Enable timer1.  ICES0 is set to 0 for falling edge detection on input capture pin.
  TCCR1B = _BV(CS10);
  // Enable input capture interrupt
  TIMSK1 |= _BV(ICIE1);
  // Enable external interrupt INT0 on pin 2 with falling edge.
  EIMSK = _BV(INT0);
  EICRA = _BV(ISC01);
}

//_______________________________________________ Системная часть. Захват изображения. Трогать не рекомендую. __________________________
//______________________________________________________________________________________________________________________________________
void initInputProcessing()
{
  // Analog Comparator setup
  ADCSRA &= ~_BV(ADEN); // disable ADC
  ADCSRB |= _BV(ACME); // enable ADC multiplexer
  ADMUX &= ~_BV(MUX0);  // select A2 for use as AIN1 (negative voltage of comparator)
  ADMUX |= _BV(MUX1);
  ADMUX &= ~_BV(MUX2);
  ACSR &= ~_BV(ACIE);  // disable analog comparator interrupts
  ACSR &= ~_BV(ACIC);  // disable analog comparator input capture
}

//________________________ Полагаю активация возможности обработки кадра. Системная часть. Трогать не рекомендую. ____________________________
//____________________________________________________________________________________________________________________________________________
// Required
ISR(INT0_vect) 
{
  display.scanLine = 0;
}

//_________________________________________ Захват данных с изображения построчно. Получение координат. ______________________________________
//____________________________________________________________________________________________________________________________________________
void loop() 
{
  tv.capture();
  // uncomment if tracking dark objects
  tv.fill(INVERT);
  boolean found = false;
  fs = false;
  for(int y=0;y<H;y++) 
  { 
      minX=W-20;
      maxX=20;
      stp = false;
      found = false;
    for(int x=20;x<W-20;x++) 
    { 
      c = tv.get_pixel(x,y);
      if (c == 1) 
      {
        if (!fs)
        {
          Ymax = y;
        }
        found = true;
        if (x < minX) 
        {
          minX = x;
        }
        if (x > maxX) 
        {
          maxX = x;
          //Xmin = x;
        }
        if (y < minY) 
        {
          minY = y;
        }
        if (y > maxY) 
        {
          maxY = y;
        }
      }
    }
    if (y == 80)
    {
      if (maxX+minX > last)
      {
        stp = true;
      }
    }
    last = maxX-minX;
    if (stp == true)
    {
      digitalWrite(5, HIGH);
    }
    else
    {
      digitalWrite(5, LOW);
    }
    
    /*if (!fs)
    {
      Xmax = (maxX+minX)/2;
      Ymax = y;
    }
    if  (y == 96)
    {
      Xmin = (maxX+minX)/2;
    }
    if (found && !fs)
    {
      fs = true;
    }*/
    if (found == true)// ----------- Для визуализации середины черной линии. ---------
       x1= (maxX+minX)/2; 
    else 
       x1= 0;  
    X[y]=x1; //-------- Заполнение массива координат черной линии. ---------
  }
//____________________________________________________ Угол ищем. __________________________________________________
//__________________________________________________________________________________________________________________
 Xmax = X[0];
 Xmin = X[95];
 Ymax = 0;
Ymin = 96;
X2 = W/2-W/2; 
Y2 = 0-H;
X1 = Xmax-Xmin;
Y1 = Ymax-Ymin;
  //deg = (Y2*Y1)/(96*sqrt(X1*X1+Y1*Y1));
  deg = (X2*Y2+X1*Y1)/(sqrt(X2*X2+Y2*Y2)*sqrt(X1*X1+Y1*Y1));
  degr= cos(deg);
  degree = acos(degr)*180/3.14;
  if (Xmax > W/2)
  {
    degree -= 2*degree;
  }
  Serial1.write(int(degree));
  
//______________________________________________________ Работа с оверлеем. ________________________________________
//__________________________________________________________________________________________________________________
  // draw bounding box
  tv.fill(0);
 
  
  for (int i = 0; i< H; i++)
  {
    tv.set_pixel(W/2,i,1);
    /*if (X[i]!= 0)
    {
      tv.set_pixel(X[i]-2,i,1);
    }*/
  }
  tv.draw_line(Xmin,Ymin,Xmax,Ymax,1);
  tv.draw_line(20,78,100,80,1);
  tv.print (0,0,degree);
//_________________________________________________ Окончание работы с кадром. Закрытие. ____________________________
//___________________________________________________________________________________________________________________
  tv.resume();
  tv.delay_frame(2);
}

 

