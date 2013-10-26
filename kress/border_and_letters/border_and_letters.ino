
#define MODES_ALL_ON 1
#define MODES_RANDOM 2
#define MODES_LADDER 3

#define A  2
#define B  3
#define C  4
#define D  5
#define E  6
#define FF  7
#define G  8
#define H  9

int currentMode = MODES_ALL_ON;

int MODE_INPUT_PIN = A2;

void allOff()
{
  setAll(LOW);
}

void allOn()
{
  setAll(HIGH);
}


// remove after testing
const int ledPin =  13;      // the number of the LED pin
const int ledPin2 = 12;
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 1000;           // interval at which to blink (milliseconds)
// end of test varialbes

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
    setAll(ledState);
  }  
}

void bottomElOn()
{
  digitalWrite(A, HIGH);
  digitalWrite(D, HIGH);

}

void loop()
{   
  currentMode = analogRead(MODE_INPUT_PIN);

  switch(currentMode)
  {
    case 0:
    {
         currentMode = MODES_ALL_ON;
         Serial.println(currentMode);
         break;
    } 
    case 20:
    {
      currentMode = MODES_RANDOM;
      break;
    }
    case 40:
    {
      currentMode = MODES_LADDER;
    }
    default:
    {
        Serial.println(currentMode);
    }
  }
  
//  currentMode = 40;
  
  switch(currentMode)
  {
    case MODES_ALL_ON:
    {
      allOn();
      break;
    }
    case MODES_RANDOM:
    {
      randomly();
    }
    // ladder mode
    case 40:
    {

    }
    case 41:
    {

    }
    case 42:
    {
      allOff();
      break;
    }
    case 43:
    {
      bottomElOn();
      break;
    }
    case 44:
    {
      bottomElOn();
      topElOn();
      break;
    }       
    default:
    {
      allOn();
    }
  }
}

void randomly()
{
/*
  int b;
  int state;
  
  for(int i=A; i<=H; i++) 
  {
    b = random(2);
    state = i == 0 ? LOW : HIGH;
    digitalWrite(i, state);
  }  
*/

blink();
}

void setAll(int mode)
{
     digitalWrite(A, mode); 
     digitalWrite(B, mode); 
     digitalWrite(C, mode); 
     digitalWrite(D, mode); 
     digitalWrite(E, mode); 
     digitalWrite(FF, mode); 
     digitalWrite(G, mode); 
     digitalWrite(H, mode);    
}

void setup() 
{
  pinMode(MODE_INPUT_PIN, INPUT);
  randomSeed( analogRead(A5) );

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(FF, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(H, OUTPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}

void topElOn()
{
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

