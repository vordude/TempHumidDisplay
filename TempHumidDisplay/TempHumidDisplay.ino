/*-----( Import needed libraries )-----*/
#include <Wire.h>  

// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>
// https://github.com/practicalarduino/SHT1x
#include <SHT1x.h>

// set the LCD address to 0x20 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address


// 8  RED Power
// 9  GRN Ground
// 10 BLU Data
// 11 YEL Clock

#define dataPin1  10
#define clockPin1 11
#define powerPin1 8
#define lowPin1 9

#define dataPin2  6
#define clockPin2 7
#define powerPin2 4
#define lowPin2 5

SHT1x sht1x_one(dataPin1, clockPin1);
SHT1x sht1x_two(dataPin2, clockPin2);


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(16,2);         // initialize the lcd for 20 chars 4 lines and turn on backlight
  // Supplying voltage to the sensor with pin 8.  Probably not right, but functional
  pinMode(8, OUTPUT);
  // Sensor's ground is 9, doing it here, probably shouldn't?
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
   
  // Same as the first... 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
}


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{  
  float temp_f_1;
  float humidity_1;
  // Give the sensor 5v.
  digitalWrite(8, HIGH);
  // Wait a moment, before reading.  (this helps)
  delay(500);
  // Get the numbers.
  temp_f_1 = sht1x_one.readTemperatureF();
  humidity_1 = sht1x_one.readHumidity();
  // Shut down the voltage to the sensor.
  digitalWrite(8, LOW);

  // Second verse, same as the first.
  float temp_f_2;
  float humidity_2;
  digitalWrite(4, HIGH);
  delay(500);
  temp_f_2 = sht1x_one.readTemperatureF();
  humidity_2 = sht1x_one.readHumidity();
  digitalWrite(4, LOW);

  // Output the results.
  //Start at character 0 on line 0
  lcd.setCursor(0,0); 
  lcd.print(temp_f_1);
  lcd.print ("F - ");
  lcd.print(humidity_1);
  lcd.print ("%");

  lcd.setCursor(0,1); //Start at character 0 on line 1
  lcd.print(temp_f_2);
  lcd.print ("F - ");
  lcd.print(humidity_2);
  lcd.print ("%");
  // Wait a minute, then do it again.
  delay(60000);
}

