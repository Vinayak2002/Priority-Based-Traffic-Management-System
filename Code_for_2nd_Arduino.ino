#include <Wire.h>
#include <LiquidCrystal_I2C.h>

struct lane_intensity {
  String l1;
  String l2;
};

String convert(int x);
void lcdDisplay(struct lane_intensity a);


LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Welcome");

  Wire.begin(4);               
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);           
}

void loop()
{
  delay(1000);
}

String convert(int x)
{
  if (x == 0) return "EMPTY";
  else if (x == 1) return "LOW";
  else if (x == 2) return "MEDIUM";
  else return "HIGH";
  
}

void lcdDisplay(struct lane_intensity a)
{
  lcd.setCursor(0,0);
  lcd.print("Lane 1: ");
  lcd.print(a.l1);
  lcd.setCursor(0,1);
  lcd.print("Lane 2: ");
  lcd.print(a.l2);
  
}

void receiveEvent(int howMany)
{
  int x = Wire.read();    // receive byte as an integer
  int y = Wire.read();
  Serial.println(x);         // print the integer
  Serial.println(y);
  struct lane_intensity out;
  out.l1 = convert(x);
  out.l2 = convert(y);
  lcdDisplay(out);
  
}
