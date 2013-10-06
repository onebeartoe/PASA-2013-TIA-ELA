
#include <Adafruit_NeoPixel.h>

#define N_PIXELS  30  // Number of pixels in strand

#define LED_PIN    6  // NeoPixel LED strand is connected to this pin

byte
  peak      = 0,      // Used for falling dot
  dotCount  = 0,      // Frame counter for delaying dot-falling speed
  volCount  = 0;      // Frame counter for storing past volume data

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

//int height = 30;

long inches;

// light modes
#define MODES_ALL_ON 1
#define MODES_MOTION_DETECTED_A 2

int currentMode = MODES_ALL_ON;

int motionDetectedAHeight = 0;

int spireSequencerPin = 9;  // connected digital pin 9

void loop()
{ 
  if (Serial.available())
  {
    currentMode = Serial.read() - '0';
  }
  
  switch(currentMode)
  {
    case MODES_ALL_ON:
    {
      analogWrite(spireSequencerPin, 0);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
      neoPixelsLadder(N_PIXELS, 500);
      
      break;
    }
    case MODES_MOTION_DETECTED_A:
    {
        analogWrite(spireSequencerPin, 1023);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
      motionDetected();
      break;
    }
    default:
    {
      neoPixelsLadder(3, 500);      
    }
  }
}

void motionDetected()
{
  motionDetectedAHeight++;
  
  if(motionDetectedAHeight > N_PIXELS)
  {
    motionDetectedAHeight = 0;
  }
  
  neoPixelsLadder(motionDetectedAHeight, 20);
  
//  delay(20);
}

void neoPixelsLadder(int height, long msDelay)
{
  uint8_t  i;

  if(height < 0)
  {
    height = 0;
  }
  
  if(height > N_PIXELS)
  {
    height = N_PIXELS;
  }

  // Color pixels based on rainbow gradient
  for(i=0; i<N_PIXELS; i++) 
  {
    if(i >= height)               
      strip.setPixelColor(i,   0,   0, 0);
    else 
      strip.setPixelColor(i,Wheel(map(i,0,strip.numPixels()-1,30,150)));    
  }
 
  delay(msDelay);
  
   strip.show(); // Update strip
}


void setup() 
{
//  pinMode (2,OUTPUT);//attach pin 2 to vcc
//  pinMode (5,OUTPUT);//attach pin 5 to GND
  
  pinMode(spireSequencerPin, OUTPUT);   // sets the pin as output
  
  // initialize serial communication:
  Serial.begin(9600);

  strip.begin();
}


// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) 
{
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


