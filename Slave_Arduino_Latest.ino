#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

char value[2]={'0','0'};
int HIGH_TIME=15000;
int MED_TIME=10000;
int LOW_TIME=5000;
int E_TIME=1000;
String convert(char x);

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
   
  Serial.begin(9600);    

  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    radio.read(&value, sizeof(value));
    Serial.println(value);
  }
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("Lane 1: ");
  lcd.print(convert(value[0]));
  lcd.setCursor(0,1);
  lcd.print("Lane 2: ");
  lcd.print(convert(value[1]));
  if(value[0]==value[1])
  {
    if(value[0]=='0')
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
    else if(value[0]=='1')
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
    else if(value[0]=='2')
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
  else if(value[0]>value[1])
  {
    if (value[0] == '1')
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(LOW_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }                                

    if (value[0] == '2')
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(MED_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }

    if (value[0] == '3')
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(HIGH_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }


    if (value[1] == '0')
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(E_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }

    if (value[1] == '1')
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(LOW_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }
  
    if (value[1] == '2')
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
    if (value[1] == '1')
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(LOW_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
     
    }                                

    if (value[1] == '2')
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(MED_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }

    if (value[1] == '3')
    {
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      delay(HIGH_TIME);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
    }


    if (value[0] == '0')
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(E_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }

    if (value[0] == '1')
    {
      digitalWrite(4,HIGH);
      digitalWrite(7,HIGH);
      delay(LOW_TIME);
      digitalWrite(4,LOW);
      digitalWrite(7,LOW);
    }
  
    if (value[0] == '2')
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

String convert(char x)
{
  if (x == '0') return "EMPTY";
  else if (x == '1') return "LOW";
  else if (x == '2') return "MEDIUM";
  else return "HIGH";
  
}
