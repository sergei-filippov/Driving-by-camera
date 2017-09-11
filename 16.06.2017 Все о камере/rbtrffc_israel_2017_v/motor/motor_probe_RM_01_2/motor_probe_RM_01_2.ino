
#include <Servo.h>

int serva=15, //__________Проверить куда подключён мотор!!!___________
    i,led,
    di=1,
    delay_t=40;     //"delay_t=40" - это граница у меня. При "40" может не сработать.
                    // Ниже 40 задний ход не включается, выше включается. Передний ход работает!
                    // Если раскоментить строку с циклом "for" (см. ниже),
                    // то "delay_t" может быть любой -- вплоть до "0".
                    
        // _____Обратить внимание на ДВА куска в конце -- с прямым указанием "delay (600)" и "delay (700)"
            
Servo servom;
void setup() {
pinMode(13,OUTPUT);
//pinMode(15,OUTPUT);
  servom.attach(serva);
  delay(2000);
  Serial.begin(9600);
  
   for(led = 0; led<10; digitalWrite (13,1), delay (100), digitalWrite (13,0), delay (100),led++);
}
void loop() {

  for( i = 90; i<=180;i=i+di){
     servom.write(i);
     delay(delay_t);
     Serial.println(i);
  }

  //di=-di;
   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}
  
  for( i = 180; i>=90;i--){
     servom.write(i);
     delay(delay_t);
     Serial.println(i);
  }
 //  ------------------
 //  for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}
 //  ------------------
 
     for( i = 90; i>=0;i--){
     servom.write(i);
     delay(delay_t);
     Serial.println(i);
  }
  
   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}

    for(i = 0; i<=90;i++){
     servom.write(i);
     delay(delay_t);
     Serial.println(i);
  }
   
   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}

  servom.write(103); 
  delay (2000);
    servom.write(90);
  delay (600);           // Тут задний не включается!!!
    servom.write(75);
    delay (2000);

   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}

   servom.write(103);
  delay (2000);
    servom.write(90);
  delay (700);            // А тут включается!!!
    servom.write(75);
    delay (2000);

   for(led = 0; led<10; led++)  {digitalWrite (13,1); delay (100); digitalWrite (13,0); delay (100);}
}
