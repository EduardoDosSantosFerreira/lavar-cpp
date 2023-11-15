#include <LiquidCrystal.h>
#include <Servo.h>
#include <IRremote.h>

// Para iniciar pressione o botão ou o número 0 no controle remoto //

int led1= 0;
int led2= 1;
int led3= 2;
int enable1 = 3;
int input1 = 4;
int input2 = 5;
int button1 = 6;
IRrecv irrecv = 7;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int sensor1 = A3;
int buzzer = A4;

int val;
float tempo;
bool isRedOn = false;


decode_results results;

Servo servo1;
Servo servo2;
Servo servo3;



void setup()
{ 
 lcd.begin(16,2);
 lcd.clear();
 lcd.print("Bem vindo");
 delay(1000);
 lcd.clear();
 lcd.print("Pressione o");
 lcd.setCursor(0,1);
 lcd.print("botao");
 delay(1000);
  
 pinMode(input1, OUTPUT);
 pinMode(enable1,OUTPUT);
 pinMode(input2, OUTPUT);
 pinMode(led1,   OUTPUT);
 pinMode(led2,   OUTPUT);
 pinMode(led3,   OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(sensor1, INPUT);
 pinMode(button1, INPUT);
    
 servo1.attach(A0);
 servo2.attach(A1);
 servo3.attach(A2);
  
 //Serial.begin(9600);
  
 irrecv.enableIRIn();   
}


void beep()
{
 analogWrite(buzzer, 150);
 delay(50);
 analogWrite(buzzer,0);
}


void rotateLeft()
{
 digitalWrite(enable1, HIGH);  
 digitalWrite(input1, HIGH);
}
 

void rotateRight()
{
 digitalWrite(enable1, HIGH);
 digitalWrite(input2, HIGH);
}
 

void parar()
{
 digitalWrite(enable1, LOW);
 digitalWrite(input1, LOW);
 digitalWrite(input2, LOW);
}
 

void abreTampa()
{
 servo3.write(90);
}


void fechaTampa()
{
 servo3.write(0);
}


void texto1()
{
 lcd.clear();
 lcd.print("TAMPA ABERTA!");
 delay(1500);
}


void texto2()
{
 lcd.clear();
 lcd.print("  Pressione o   ");
 lcd.setCursor(0,1);
 lcd.print("     botao!     ");
}


void timer0()
{
 lcd.setCursor(0,1);
 lcd.print(tempo);
 lcd.print(" seg(s)");
}


void timer1()
{
 lcd.setCursor(0,1);
 lcd.print(tempo++);
 lcd.print(" seg(s)");
}


void timer2()
{
 lcd.setCursor(0,1);
 lcd.print(tempo=tempo+2.5);
 lcd.print(" seg(s)");  
}


void controleremoto()
{ 
 if(irrecv.decode(&results))
  { 
   //Serial.println(results.value, HEX); 
   switch (results.value) 
    {
     case 0xFD30CF: //botao0
       beep();
       fechaTampa();
       digitalWrite(led3,HIGH);
       operacao();
       abreTampa();
 	   delay(5000);
       break;
      
     case 0xFD08F7:  //botao1  
      
       break;
     
     case 0xFD8877:  //botao2  
      
       break;
     
     case 0xFD48B7:  //botao3  
      
       break;
     
     case 0xFD28D7:  //botao4  
      
       break;
     
     case 0xFDA857:  //botao5  
      
       break;
     
      case 0xFD6897: //botao6   
      
       break;
               
     case 0xFD18E7:  //botao7   
      
       break;     
     
     case 0xFD9867:  //botao8   
      
       break;     
     
     case 0xFD58A7:  //botao9
      
      break; 
    }
    irrecv.resume();  
  }
}


void operacao()
{
	       //Encher com água
   	  for(int cont=0;cont<5;cont++)   
      	   {	  
            digitalWrite(led1,HIGH);
            lcd.clear();
            lcd.print("Enchendo. . .");
		    timer1();
		    servo1.write(0); 
 		    delay(1000);
            timer1();
		    servo1.write(90); 
 		    delay(1000);
        
           }    
   		
    		    //Esfregar
   	  for(int cont=0;cont<5;cont++)
       	   {
        	digitalWrite(led1,LOW);
            digitalWrite(led2,HIGH);   
            lcd.clear();
            lcd.print("Esfregando. . .");
            timer0();
            rotateLeft();
		    delay(2000);
		    parar();
            delay(500);
            timer2();
		    rotateRight();
		    delay(2000);
            parar();
            delay(500);
            timer2();
           }
    
    			// Repouso
   	  for(int cont=0;cont<5;cont++)
           {
        	digitalWrite(led2,LOW);
    		digitalWrite(led1,HIGH);
    		lcd.clear();
        	lcd.print("De molho. . .");
    		timer0();
  			delay(1000);
           	timer1();
           }
    
  				// Retirar a água
   	  for(int cont=0;cont<5;cont++)
           {
        	digitalWrite(led1,LOW);
           	digitalWrite(led2,HIGH);
            lcd.clear();
            lcd.print("Esvaziando. . .");
           	timer1();
            servo2.write(0); 
 			delay(1000);
           	timer1();
			servo2.write(90); 
 			delay(1000);
    	   }
  
  				// Centrifugar
   	  for(int cont=0;cont<10;cont++)
           {
        	digitalWrite(led2,LOW);	
   			digitalWrite(led1,HIGH);     
			lcd.clear();
			lcd.print("Centrifugando. . .");
   			timer0();
			rotateLeft();
		    delay(1000);
            timer1();
           }
 
 parar();
 digitalWrite(led2,HIGH);
 lcd.clear();
 lcd.print("Roupa lavada !!!!");
 timer0();
}



void loop()
{
  controleremoto();
  
  switch (digitalRead(button1)) 
   {
     case HIGH: 
       beep();
       fechaTampa();
       digitalWrite(led3,HIGH);
       operacao();
       abreTampa();
 	   delay(5000);
       beep();
       break;
      
     case LOW:    
      
       break;
   }
  switch (digitalRead(sensor1)) 
   {
     case HIGH: 
       abreTampa();
        break;
      
     case LOW:    
       fechaTampa();
        break;
   }  
  
   
}
 