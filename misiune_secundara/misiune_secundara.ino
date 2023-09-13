#include <SoftwareSerial.h>      // Include software serial library
#include <TinyGPS++.h>       // Include TinyGPS++ library
#include <STM32_ISR_Timer.h>     //Timer for interrupting (VCO)

//serial for gps pins (check datasheet)
#define S_RX    2                // Define software serial RX pin
#define S_TX    3               // Define software serial TX pin
 
SoftwareSerial SoftSerial(S_RX, S_TX);    

TinyGPSPlus gps;

int led_pin = 13;
char start_time[]  = "TIME:00:00:00";

void getStartTime()
{
  if(SoftSerial.available() > 0)
  {
    if (gps.encode(SoftSerial.read()))
    {
      if (gps.time.isValid())
      {
        start_time[5]  = gps.time.hour()   / 10 + 48;
        start_time[6]  = gps.time.hour()   % 10 + 48;
        start_time[8]  = gps.time.minute() / 10 + 48;
        start_time[9]  = gps.time.minute() % 10 + 48;
        start_time[11] = gps.time.second() / 10 + 48;
        start_time[12] = gps.time.second() % 10 + 48;
      }
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  SoftSerial.begin(9600);

  delay(90000);


  getStartTime();

  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, HIGH); //final setup pocketqube
}

void loop() {
  // put your main code here, to run repeatedly:

}
