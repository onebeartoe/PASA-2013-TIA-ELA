
#include <Adafruit_NeoPixel.h>

#define N_PIXELS  125  // Number of pixels in strand

#define LED_PIN    6  // NeoPixel LED strand is connected to this pin

// light modes
#define MODES_ALL_ON 1
#define MODES_RANDOM 2
#define MODES_LADDER 4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

//int currentMode = 172543;
int currentMode = MODES_ALL_ON;

int motionDetectedAHeight = 0;

int spireSequencerPin = 9;  // connected digital pin 9

// remove after testing
const int ledPin =  13;      // the number of the LED pin
const int ledPin2 = 12;
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)
// end of test varialbes


int leftLightPin = 10;

int rightLightPin = 11;

int subladderMode = 0;

void blink()
{
  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
    digitalWrite(ledPin2, ledState);
  }  
}

void elLadder()
{
  switch(subladderMode)
  {
    case 0:
    {
      analogWrite(spireSequencerPin, 40);
      break;
    }

    case 1:
    {
      analogWrite(spireSequencerPin, 41);
      break;
    }

    case 2:
    {
      analogWrite(spireSequencerPin, 42);
      break;
    }

    case 3:
    {
      analogWrite(spireSequencerPin, 43);
      break;
    }

    case 4:
    {
      analogWrite(spireSequencerPin, 44);
      break;
    }
    default:
    {
      subladderMode = -1;
    }
  }
  subladderMode++;
  
//  delay(300);
}

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

digitalWrite(ledPin, HIGH);
digitalWrite(ledPin2, HIGH);
      
      break;
    }
    case MODES_RANDOM:
    {
      analogWrite(spireSequencerPin, 20);
blink();
//      randomly();
      
      break;
    }
    case MODES_LADDER:
    {
      elLadder();
      
      break;
    }    
    default:
    {
      blink();
    }
  }
}

boolean yellowLights = true;

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
  // dummy pin for on-board LED
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
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

