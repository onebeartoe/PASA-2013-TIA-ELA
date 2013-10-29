
int dataPin = 2;              // The Serial Data Pin to the Shift Register
int latchPin = 3;             // The Latch Pin to the Shift Register
int clockPin = 4;             // The Clock Pin to the Shift Register

byte leds_1_8;

void allOn()
{
  setAll(HIGH);  
  updateShiftRegister();  
}

void loop()
{
}

void setAll(int state)
{
  for (int i = 0; i < 8; i++)
  {
    if(state == HIGH)
    {
      bitSet(leds_1_8, i);      
    }
    else
    {
      bitClear(leds_1_8, i);
    }
  }  
}

void setup()
{
  pinMode(dataPin, OUTPUT);    // Configure Digital Pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);  
  
  allOn();
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
//  shiftOut(dataPin, clockPin, LSBFIRST, 1);
//  shiftOut(dataPin, clockPin, LSBFIRST, 1);
//  shiftOut(dataPin, clockPin, LSBFIRST, 1);
//  shiftOut(dataPin, clockPin, LSBFIRST, 1);
  
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  digitalWrite(latchPin, HIGH);
}

