//Made by Advay Kavathekar
//Binary Clock Code for Mr. DeRafelo

#include <DS3231.h>    // includes the clock library


DS3231 rtc(SDA, SCL);    //  sets ds3231 rtc module to sda and scl pins (sda:4, scl:5)

const int srclock = 4;       // sets IC shift register clock to pin 6
const int orclock = 3;       // sets IC output clock to pin 3
const int ser = 2;           // sets IC serial to pin 2


void setup() {
  
Serial.begin(115200);     // starts serial monitor


rtc.begin();     // library function that starts the rtc clock


//rtc.setDOW(TUESDAY);         // sets day of week to tuesday
//rtc.setTime(10,31,30);         // sets time to ____
//rtc.setDate(10,2,2026);      // sets date

pinMode(srclock, OUTPUT);       // sets pinmodes
pinMode(orclock, OUTPUT);
pinMode(ser, OUTPUT);
}


void loop() {
   

   String time = rtc.getTimeStr();    // sets time = the time
   char secondones = time[7];         //takes each place in the index of the time string
   char secondtens = time[6];
   char minuteones = time[4];
   char minutetens = time[3];
   char hourones = time[1];
   char hourtens = time[0];

   int secondsones = secondones - '0';     // converts char to integer
   int secondstens = secondtens - '0';
   int minutesones = minuteones - '0';
   int minutestens = minutetens - '0';
   int hoursones = hourones - '0';
   int hourstens = hourtens - '0';


   byte secondsByte = 0;       // creates new byte to send to each IC
   byte minutesByte = 0;
  byte hoursByte = 0;

   secondsByte |= secondsones;           //adds the ones place and tens place into one byte to send over
   secondsByte |= (secondstens << 4);    // assembles all three bytes and shifts over the tens values into the byte
   minutesByte |= minutesones;
   minutesByte |= (minutestens << 4);
   hoursByte |= hoursones;
   hoursByte |= (hourstens << 4);

   digitalWrite(orclock, LOW);                        //sets output clock to low to not show any of the data

   shiftOut(ser, srclock, MSBFIRST, hoursByte);       //shifts out all of the data to serial pin. Clock pin is srclock, mostsignificant bit first, the actual data to shift.
   shiftOut(ser, srclock, MSBFIRST, minutesByte);
   shiftOut(ser, srclock, MSBFIRST, secondsByte);
  
   digitalWrite(orclock, HIGH);                       // sets output clock to high to show all of the data
  
   Serial.print(secondsones);       //prints the different values into serial monitor to view for debugging.
   Serial.print(" ");
   Serial.print(secondstens);
   Serial.print(" ");
   Serial.print(hoursByte, BIN);
   Serial.print(" ");
   Serial.print(minutesByte, BIN);
   Serial.print(" ");
   Serial.print(secondsByte, BIN);
   Serial.print(" ");

   Serial.print(rtc.getTimeStr());
   Serial.println("");

   

  delay(1000);                      // waits 1 second, to send out new data every second.
}



