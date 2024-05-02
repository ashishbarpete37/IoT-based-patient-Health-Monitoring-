#include <Wire.h> // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h> // Include the LiquidCrystal_I2C library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows

int val;
int tempPin = A0; // Temperature Sensor Pin
int HBSensor = 8; // Heartbeat Sensor Pin
int HBCount = 0;
int HBCheck = 0;
int TimeinSec = 0;
int HBperMin = 0;
int HBStart = 2;
int HBStartCheck = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight(); // Turn on the backlight
  pinMode(HBSensor, INPUT);
  pinMode(HBStart, INPUT_PULLUP);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("PR:");
  lcd.setCursor(11, 1);
  lcd.print("BT:");
}
void timerIsr() {
    TimeinSec = TimeinSec + 1;
    lcd.setCursor(0, 0);
    lcd.print("Time-in-Sec:");
    lcd.print(TimeinSec);}

void loop() {
  val = analogRead(tempPin);
  float mv = (val / 1023.0) * 5000;
  int cel = mv / 10;
  lcd.setCursor(14, 1);
  lcd.print(cel);
  delay(3000);

  timerIsr();

{
    if ((digitalRead(HBSensor) == 1)) {
      HBCount = HBCount + 1;
    }
    else {}


    if (TimeinSec == 10) {
      HBperMin = HBCount * 6;
      lcd.setCursor(3,1);
      lcd.print(HBperMin);
      HBCount = 00;
      TimeinSec = 00;
    }
  }
}