#include <Time.h>
#include <TimeLib.h>
#include <SevenSegmentAsciiMap.h>
#include <SevenSegmentTM1637.h>


const byte PIN_CLK = 7;   // define CLK pin (any digital pin)
const byte PIN_DIO = 8;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

unsigned long relationship = 1610150400 ;  //in unixtime relationship started
unsigned long days ;
unsigned long days_prev; 
int weeks ;


void setup() {
  Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
  display.begin();            // initializes the display
  display.clear();
  display.setBacklight(10);  // set the brightness to 100 %
  LoveYouLcd();
  delay(50);                // wait 1000 ms
  adjustTime(1643049780);
  days_prev = 0;
  days = 0;
  
}

void loop() {
  days = ((now() - relationship) / 86400); //magic nubmer 86400 is the number of seconds in a day       
  time_t t = now();
  serialprintdate();
 
  
  if ( 9 == day(t)  &&  1 == month(t)  ) 
  {
    delay(5000); 
    LoveYouLcd() ;
    AnniversaryLcd() ; 


  }


  if (days - days_prev >= 1)
  {
    ShowDaysReading();
    days_prev = (days);
  }

 
}

void ShowDaysReading()
{  
  ClearLcd() ;  
  days = ((now() - relationship) / 86400); //magic nubmer 86400 is the number of seconds in a day
  weeks = ((now() - relationship) / (86400 * 7) ); //magic nubmer 86400 is the number of seconds in a day
  if (days<=99999999 && days>=10000) 
  {
    if (weeks<=9999 && weeks>=1000) 
    {
      display.print(weeks); 
      delay(5000); 
      display.print("7day"); 
      delay(1000); 
    }
    if (weeks<=999 && weeks>=100) 
    {
      display.print("0"); 
      display.print(weeks); 
      delay(5000); 
      display.print("7day"); 
      delay(1000); 
    }

    if (weeks<=99 && weeks>=10) 
    {
      display.print("00"); 
      display.print(weeks); 
      delay(5000); 
      display.print("7day"); 
      delay(1000); 
    }

    if (weeks<=9 && weeks>=0) 
    {
      display.print("000"); 
      display.print(weeks); 
    }
  }

  //days
  if (days<=9999 && days>=1000) 
  {
    display.clear();
    display.print(days); 

  }
  if (days<=999 && days>=100) 
  { 
    display.print(days); 

  }

  if (days<=99 && days>=10) 
  {
    display.print("00"); 
    display.print(days); 

  }

  if (days<=9 && days>=0) 
  {
    display.print(days); 

  }
}

void ClearLcd() 
  {  
   display.clear();
}

void LoveYouLcd() 
  {  
  display.clear(); 
  display.print("LOUE");  //Love
  delay(2500);
  display.clear(); 
  display.print("YOU ");  //You
  delay(2500);
  display.clear();    
}

void AnniversaryLcd() 
  {  
 
    display.print("jEn"); //Jennifer
    delay(2500); 
    display.print("LIA");  //Liam
    delay(1500);    
    display.print("For");  //For
    delay(1500);
    display.print("EVER");  //Ever
    delay(1500);
 }

void serialprintdate()
  {
    Serial.print("today is ");
    Serial.print(month());
    Serial.print("/");
    Serial.print(day());
    Serial.print("/");
    Serial.println(year());
  }
