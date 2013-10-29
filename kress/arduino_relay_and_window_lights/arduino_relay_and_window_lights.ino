
// window light modes
#define MODES_ALL_ON 1
#define MODES_BLINK 2
#define MODES_KNIGHT_RIDER_2009 3

//int currentMode = 172543;
//int currentMode = MODES_ALL_ON;
int currentMode = MODES_BLINK;
//int currentMode = MODES_ALL_ON;

// pins used by the shift registers
int dataPin = 2;              // The Serial Data Pin to the Shift Register
int latchPin = 3;             // The Latch Pin to the Shift Register
int clockPin = 4;             // The Clock Pin to the Shift Register

int spireSequencerPin = 10;  // connected digital pin 10

byte leds_1_8;

// counter for ladder mode
int ladderHeight;

//int ladderByte1 [];

// knight rider
int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2};
int seq2[14] = {128,64,32,16,8,4,2,1,2,4,8,16,32,64};
int value = 0;
int value2 = 0;


void allOff()
{
  setAllWindows(LOW);  
  updateShiftRegister();  
}

void allOn()
{
  setAllWindows(HIGH);  
  updateShiftRegister();  
}

void blink()
{
   allOn();
   delay(300);
   
   allOff();
   delay(300);
}

void defaultMode()
{
  boolean bits []= {true,false,true,false,true,false,true,false};
  byte b = setByte(bits);
  byte bytes [] = {0,0,b,0};
  
  updateShiftRegister(bytes);
}

void knightRider()
{
  for (int n=0; n < 14; n++)
  {
    value = seq[n];             //Forward array
    value2 = seq2[n];          //Reverse array
    
    writeKnightRiderOutput();
    
    delay(75);
  }  
}

void loop()
{ 
  if (Serial.available())
  {
    currentMode = Serial.read() - '0';
    Serial.print(currentMode);
  }
  
  int pinData;
  
  switch(currentMode)
  {
    case MODES_ALL_ON:
    {
      pinData = 10;
      
      allOn();
      
      break;
    }
    case MODES_BLINK:
    {
      pinData = 20;
      
      blink();
      
      break;
    }
    case MODES_KNIGHT_RIDER_2009:
    {
      pinData = 30;
      knightRider();
      
      break;
    }
    default:
    {
      pinData = 100;
      
      defaultMode();
    }
  }
  
  // relay the mode to the other microcontrollers
  analogWrite(spireSequencerPin, pinData);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
  
  Serial.print(currentMode);
}

void setAllWindows(int state)
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

byte setByte(boolean bits[])
{
  byte b = 0;
  
  for(int i=0; i<8; i++)
  {
    if(bits[i])
    {
      bitSet(b, i);
    }
    else
    {
      bitClear(b,i);
    }
  }
  
  return b;
}

void setup() 
{
  // Configure Digital Pins used by the 4 shift registers
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
    
//  pinMode(spireSequencerPin, OUTPUT);   // sets the pin as output
  
  // initialize serial communication:
  Serial.begin(9600);
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  shiftOut(dataPin, clockPin, LSBFIRST, leds_1_8);
  digitalWrite(latchPin, HIGH);
}

void updateShiftRegister(byte bytes [])
{
  digitalWrite(latchPin, LOW);
  
  for(int i=0; i<4; i++)
  {
    shiftOut(dataPin, clockPin, LSBFIRST, bytes[i]);
  }
  
  digitalWrite(latchPin, HIGH);
}

void writeKnightRiderOutput()
{
    digitalWrite(latchPin, LOW);                       // Pull latch LOW to send data
    
    shiftOut(dataPin, clockPin, MSBFIRST, value);      // Send the data byte 1
    shiftOut(dataPin, clockPin, MSBFIRST, value);      // Send the data byte 1
    shiftOut(dataPin, clockPin, MSBFIRST, value);      // Send the data byte 1
    
    shiftOut(dataPin, clockPin, MSBFIRST, value);      // Send the data byte 1
//    shiftOut(dataPin, clockPin, MSBFIRST, value2);     // Send the data byte 2

    digitalWrite(latchPin, HIGH);                      // Pull latch HIGH to stop sending data
}
