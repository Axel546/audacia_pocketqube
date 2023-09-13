#include <Wire.h>
#include <Adafruit_BMP085.h> //suporta si BMP180
#include <SPI.h>
#include <SD.h>

Adafruit_BMP085 bmp;

File myFile;

void setup() {

  Serial.begin(9600);

  if (!bmp.begin()) {
	  Serial.println("Could not find a valid BMP180 sensor, check wiring!");
	  while (1) {}
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("data.txr", FILE_WRITE);
}


void writeToSD(double temp, double pressure, double altitude)
{
  myFile.println(temp);
  myFile.println(" ");
  myFile.println(pressure);
  myFile.println(" ");
  myFile.println(altitude);
  myFile.println("\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  double temp = bmp.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.println(" *C");

  double pressure = bmp.readPressure();
    
  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" Pa");

  double altitude = bmp.readAltitude();

  Serial.print("Altitude = ");
  Serial.print(altitude);
  Serial.println(" meters");
    
  Serial.println();

  writeToSD(temp, pressure, altitude);
  

  delay(500);
}
