#include <Time.h>
#include <Wire.h>
#include <TimeLib.h>
#include <SevenSegmentAsciiMap.h>
#include <SevenSegmentTM1637.h>
#include <DS3231.h>


const byte PIN_CLK = 4;   // define CLK pin (any digital pin)
const byte PIN_DIO = 5;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

unsigned long relationship = 1610179200 ;  //in unixtime relationship started
unsigned long days ; 
int weeks ;


void setup() {
  Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
  Wire.begin();
  display.begin();            // initializes the display
  display.clear();
  display.setBacklight(100);  // set the brightness to 100 %
  LoveYouLcd();
  delay(100);                // wait 1000 ms
  setSyncProvider(unixtime())
  adjustTime(1297641590);
  
}

void loop() {
  days = ((now() - relationship) / 86400); //magic nubmer 86400 is the number of seconds in a day 
  unsigned long currentMillis = millis();   
  ShowDaysReading();     
  time_t t = now();
 
  
  if ( 9 == day(t)  &&  1 == month(t)  ) 
  {
    delay(5000); 
    LoveYouLcd() ;
    AnniversaryLcd() ; 


  }   

 
}

void ShowDaysReading()
{  
  ClearLcd() ;  
  days = ((now() - relationship) / 86400); //magic nubmer 86400 is the number of seconds in a day
  weeks = ((now() - relationship) / (86400 * 7) ); //magic nubmer 86400 is the number of seconds in a day
  display.print("w");
  display.print(B00000000,BYTE);
  display.print("v");
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
    display.print(days); 

  }
  if (days<=999 && days>=100) 
  {
    display.print("0"); 
    display.print(days); 

  }

  if (days<=99 && days>=10) 
  {
    display.print("00"); 
    display.print(days); 

  }

  if (days<=9 && days>=0) 
  {
    display.print("000"); 
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
  display.print("LOUE");
  delay(2500); 
  display.print("YOU");
  delay(2500);
  display.clear();    
}

void AnniversaryLcd() 
  {  
 
    display.print("jEn");
    delay(2500); 
    display.print("LIA");
    delay(1500);    
    display.print("Forx");
    delay(1500);
    display.print("EVER");
    display.clear();    
 }
