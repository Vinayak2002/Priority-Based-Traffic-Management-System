#include <Wire.h>
#include <LiquidCrystal_I2C.h>


int x = 0;
int y = 0;
int HIGH_TIME=15000;
int MED_TIME=10000;
int LOW_TIME=5000;
int E_TIME=1000;
String convert(int x);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(4, OUTPUT);//Green for lane 1
  pinMode(5, OUTPUT);//RED for lane 1
  pinMode(6, OUTPUT);//Green for lane 2
  pinMode(7, OUTPUT);//RED for lane 2
  digitalWrite(5,HIGH);
  digitalWrite(7,HIGH);
  lcd.begin();
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
  lcd.setCursor(0,0);
  lcd.print("Lane 1: ");
  lcd.print(convert(x));
  lcd.setCursor(0,1);
  lcd.print("Lane 2: ");
  lcd.print(convert(y));
  if(x==y)
  {
    if(x==0)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(E_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(E_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
    else if(x==1)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(LOW_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(LOW_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
    else if(x==2)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(MED_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(MED_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
    else
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(HIGH_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(HIGH_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
  }
  else if(x>y)
  {
    if (x == 1)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(LOW_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }                                

    if (x == 2)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(MED_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }

    if (x == 3)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(HIGH_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }


    if (y == 0)
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(E_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }

    if (y == 1)
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(LOW_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
  
    if (y == 2)
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(MED_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }


  }
  else
  {
    if (y == 1)
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(LOW_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
     
    }                                

    if (y == 2)
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(MED_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }

    if (y == 3)
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(HIGH_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }


    if (x == 0)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(E_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }

    if (x == 1)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(LOW_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }
  
    if (x == 2)
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(MED_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }

  }
  lcd.clear();
  
}

String convert(int x)
{
  if (x == 0) return "EMPTY";
  else if (x == 1) return "LOW";
  else if (x == 2) return "MEDIUM";
  else return "HIGH";
  
}

void receiveEvent(int howMany)
{
  x = Wire.read();    // receive byte as an integer
  y = Wire.read();
  Serial.println(x);         // print the integer
  Serial.println(y);
}
