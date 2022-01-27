#include <Time.h>
#include <TimeLib.h>
#include <SevenSegmentTM1637.h>
#include <Wire.h>
#include <DS3232RTC.h>




const byte PIN_CLK = 7;   // define CLK pin (any digital pin)
const byte PIN_DIO = 8;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

unsigned long relationship = 1610150400 ;  //in unixtime relationship started
unsigned long days ;
unsigned long days_prev;
int weeks ;


void setup()
{
    Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
    Wire.begin();
    delay(500);
    setSyncProvider(RTC.get);
    setSyncInterval(36000);
    display.begin();            // initializes the display
    display.clear();
    display.setBacklight(10);  // set the brightness to 100 %
    display.setPrintDelay(500);
    LoveMessage();
    delay(50);                // wait 1000 ms
    days_prev = 0;
    // vv REMOVE AFTER GETTING RTC Module vv
    /// adjustTime(1643111100 ); // For testing purposes only
    // ^^ REMOVE AFTER GETTING RTC Module ^^


}

void loop()
{
    // Serialprintdate(); // Used for testing date. Not important.
    days = ((now() - relationship) / 86400); //86400 is seconds in a day
    time_t t = now();

    if ( 9 == day(t)  &&  1 == month(t)  )
    {
        delay(5000);
        LoveMessage() ;
        AnniversaryMessage() ;


    }
    if (23 == day(t) && 9 == month(t))
    {
        delay(5000);
        BithdayMessage();
    }


    if (days - days_prev >= 1) // Without this display would keep refreshing and made a horrible blinking, so this was my solution without interrupts.
    {
        ShowDaysReading();
        days_prev = (days);
    }

    if (days >= 10000)
    {
        ShowDaysReading();
    }


}

void ShowDaysReading()
{
    days = ((now() - relationship) / 86400); //magic nubmer 86400 is the number of seconds in a day
    weeks = ((now() - relationship) / (86400 * 7) ); //magic nubmer 86400 is the number of seconds in a day
    if (days <= 99999999 && days >= 10000)
    {
        if (weeks <= 9999 && weeks >= 1000)
        {
            display.clear();
            display.print(weeks);
            delay(5000);
            display.print("7 DAYS");
            delay(1000);
        }
        if (weeks <= 999 && weeks >= 100)
        {
            display.clear();
            display.setCursor(0, 1);
            display.print(weeks);
            delay(5000);
            display.print("7 DAYS");
            delay(1000);
        }

        if (weeks <= 99 && weeks >= 10)
        {
            display.clear();
            display.setCursor(0, 2);
            display.print(weeks);
            delay(5000);
            display.print("7 DAYS");
            delay(1000);
        }

        if (weeks <= 9 && weeks >= 0)
        {
            display.clear();
            display.setCursor(0, 3);
            display.print(weeks);
            delay(5000);
            display.print("7 DAYS");
            delay(1000);
        }
    }

    //days
    if (days <= 9999 && days >= 1000)
    {
        display.clear();
        display.setCursor(0, 0);
        display.print(days);

    }
    if (days <= 999 && days >= 100)
    {
        display.clear();
        display.setCursor(0, 1);
        display.print(days);

    }

    if (days <= 99 && days >= 10)
    {
        display.clear();
        display.setCursor(0, 2);
        display.print(days);

    }

    if (days <= 9 && days >= 0)
    {
        display.clear();
        display.setCursor(0, 3);
        display.print(days);

    }
}


void LoveMessage()
{
    display.setPrintDelay(500);
    display.print("I LOVE YOU    ");  //Love
    delay(2500);
}

void AnniversaryMessage()
{
    display.print("HAPPY ANNIVERSARY    ");
    display.clear();
    display.print("    JENNIFER AND LIANN FOREVER    ");
}

void BithdayMessage()
{
    display.setPrintDelay(500);
    display.print("HAPPY BIRTHDAY    ");
}

void Serialprintdate()
{
    Serial.print("today is ");
    Serial.print(month());
    Serial.print("/");
    Serial.print(day());
    Serial.print("/");
    Serial.println(year());
}
