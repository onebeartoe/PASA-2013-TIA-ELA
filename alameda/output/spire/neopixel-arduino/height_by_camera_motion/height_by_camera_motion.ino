
#include <Adafruit_NeoPixel.h>

#define N_PIXELS  125  // Number of pixels in strand

#define LED_PIN    6  // NeoPixel LED strand is connected to this pin

// light modes
#define MODES_ALL_ON 1
#define MODES_MOTION_DETECTED_A 2
#define MODES_RANDOM 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int currentMode = MODES_ALL_ON;

int motionDetectedAHeight = 0;

int spireSequencerPin = 9;  // connected digital pin 9

int leftLightPin = 10;

int rightLightPin = 11;

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
      
      digitalWrite(leftLightPin, HIGH);
      digitalWrite(rightLightPin, HIGH); 

      neoPixelsLadder(N_PIXELS, 500);
      
      break;
    }
    case MODES_MOTION_DETECTED_A:
    {
      analogWrite(spireSequencerPin, 1023);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
      
      motionDetected();
      
      break;
    }
    case MODES_RANDOM:
    {
      analogWrite(spireSequencerPin, 300);
      randomly();
      break;
    }
    default:
    {
      neoPixelsLadder(3, 500);      
    }
  }
}

boolean yellowLights = true;

void motionDetected()
{
  motionDetectedAHeight++;
  
  if(motionDetectedAHeight > N_PIXELS)
  {
    motionDetectedAHeight = 0;
  }
  
  neoPixelsLadder(motionDetectedAHeight, 20);
  
  if(yellowLights)
  {
    digitalWrite(leftLightPin, HIGH);
    digitalWrite(rightLightPin, HIGH); 
  }
  else
  {
    digitalWrite(leftLightPin, LOW);
    digitalWrite(rightLightPin, LOW); 
  }
  yellowLights != yellowLights;
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

void randomly()
{
  // Color pixels based on rainbow gradient
  for(int i=0; i<N_PIXELS; i++) 
  {
    int c = random(255);
    strip.setPixelColor(i, Wheel(c) );
  }  
}

void setup() 
{
  pinMode (leftLightPin,OUTPUT);
  
  pinMode (rightLightPin,OUTPUT);
    
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


