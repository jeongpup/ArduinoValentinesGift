#include <TimeLib.h> // https://github.com/PaulStoffregen/Time
#include <SevenSegmentTM1637.h> // https://github.com/bremme/arduino-tm1637
#include <DS3232RTC.h>  // https://github.com/JChristensen/DS3232RTC/
#include <Wire.h>
DS3232RTC myRTC(false); 
const byte PIN_CLK = 9;   // define CLK pin (any digital pin)
const byte PIN_DIO = 8;   // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

/// Below Set when the relationship started in unixtime
const long relationship = 1610150400; // Sat Jan 09 2021 00:00:00 UTC+0000
unsigned long days ;
unsigned long days_prev;
int weeks ;


void setup()
{
    Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
    Wire.begin();
    myRTC.begin();
    delay(500);
    setSyncProvider(RTC.get);
    setSyncInterval(600); //sets RTC and 
    display.begin();            // initializes the display
    display.clear();
    display.setBacklight(10);  // set the brightness to 10%
    display.setPrintDelay(500); // delay before text scrolls
    delay(500);
    LoveMessage();
    delay(50);                // wait 1000 ms
    days_prev = 0;
    // vv REMOVE AFTER GETTING RTC Module vv
    /// adjustTime(1643111100 ); // For testing purposes only
    // ^^ REMOVE AFTER GETTING RTC Module ^^


}

void loop()
{
    
    days = ((now() - relationship) / 86400); //86400 is seconds in a day
    time_t t = now();
    void digitalClockDisplay();

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

void digitalClockDisplay()
{
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year());
    Serial.println();
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
