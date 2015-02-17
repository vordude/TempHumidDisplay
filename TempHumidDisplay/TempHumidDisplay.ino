/* YourDuino.com Example Software Sketch
 20 character 4 line I2C Display
 Backpack Interface labelled "LCM1602 IIC  A0 A1 A2"
 terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>
#include <SHT1x.h>

/*-----( Declare Constants )-----*/
//none
/*-----( Declare objects )-----*/
// set the LCD address to 0x20 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
// 8  RED Power
// 9  GRN Ground
// 10 BLU Data
// 11 YEL Clock



/*-----( Declare Variables )-----*/
#define dataPin1  10
#define clockPin1 11
#define powerPin1 8
#define lowPin1 9


SHT1x sht1x(dataPin, clockPin);


void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin(16,2);         // initialize the lcd for 20 chars 4 lines and turn on backlight

   pinMode(8, OUTPUT);
   pinMode(9, OUTPUT);
   digitalWrite(9, LOW);
}


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  
    float temp_f;
    float humidity;
    digitalWrite(8, HIGH);

    delay(500);

    temp_f = sht1x.readTemperatureF();
    humidity = sht1x.readHumidity();


  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print ("Temp: ");
  lcd.print(temp_f);
  lcd.print ("F");
  lcd.setCursor(0,1); //Start at character 4 on line 0
  lcd.print ("Hum:  ");
  lcd.print(humidity);
  lcd.print ("%");


  digitalWrite(8, LOW);
  delay(300000);
}/* --(end main loop )-- */

