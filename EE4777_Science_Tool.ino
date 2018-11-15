// Adafruit-RGB-LCD-Shield-Library - Version: Latest 
#include <Adafruit_RGBLCDShield.h>
#include <Servo.h>
#include <utility/Adafruit_MCP23017.h>
#define MIN 90
#define MAX 40
/*
Sarah Wade
Cassie Gietek
EE4777 Science Tools Servo Code
*/

Servo servo;
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
int pos;
int up;

void setup() 
{
  lcd.begin(16, 2);
  lcd.print("Hello World!");
  servo.attach(9);
  pos = MIN;
  servo.write(pos);
  delay(1000);
  up = 1;
}


// Reversed -> CCW MIN = 90, MAX = 0
//*
void loop() 
{
  pos = checkButtonsRev();
  servo.write(pos);
  updateScreenRev();
  delay(50);
}/**/


// Forward -> CW MIN = 90, MAX = 0
/*
void loop() 
{
  pos = checkButtons();
  servo.write(pos);
  updateScreen();
  delay(50);
}/**/

int checkButtonsRev()
{
  int newPos = pos;
  int buttons = lcd.readButtons();
  if (buttons & BUTTON_DOWN)
  {
    newPos = (pos+5) < MIN ? (pos+5) : MIN;
  }
  else if (buttons & BUTTON_UP)
  {
    newPos = (pos-5) > MAX ? (pos-5) : MAX;
  }
  else if (buttons & BUTTON_LEFT)
  {
    newPos = (pos+10) < MIN ? (pos+10) : MIN;
  }
  else if (buttons & BUTTON_RIGHT)
  {
    newPos = (pos-10) > MAX ? (pos-10) : MAX;
  }
  else if (buttons & BUTTON_SELECT)
  {
    newPos = MIN;
  }
  return newPos;
}

void updateScreenRev()
{
  lcd.clear();
  lcd.print("Position: ");
  int x = abs(pos-90);
  lcd.print(x);
}

int checkButtons()
{
  int newPos = pos;
  int buttons = lcd.readButtons();
  if (buttons & BUTTON_DOWN)
  {
    newPos = (pos-5) > MIN ? (pos-5) : MIN;
  }
  else if (buttons & BUTTON_UP)
  {
    newPos = (pos+5) < MAX ? (pos+5) : MAX;
  }
  else if (buttons & BUTTON_LEFT)
  {
    newPos = (pos-10) > MIN ? (pos-10) : MIN;
  }
  else if (buttons & BUTTON_RIGHT)
  {
    newPos = (pos+10) < MAX ? (pos+10) : MAX;
  }
  else if (buttons & BUTTON_SELECT)
  {
    newPos = MIN;
  }
  return newPos;
}

void updateScreen()
{
  lcd.clear();
  lcd.print("Position: ");
  lcd.print(pos);
}

void test()
{
  if (up == 1)
  {
    if (pos - 5 > MAX)
    {
      pos = pos - 5;
    } else {
      pos = MAX;
      up = 0;
    }
  } else {
    if (pos + 5 < MIN)
    {
      pos = pos + 5;
    } else {
      pos = MIN;
      up = 1;
    }
  }
  servo.write(pos);
  delay(1000);
}
