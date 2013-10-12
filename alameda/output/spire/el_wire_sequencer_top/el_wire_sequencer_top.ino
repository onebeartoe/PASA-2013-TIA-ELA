

#define MODES_ALL_ON 1
#define MODES_MOTION_DETECTED 2
#define MODES_RANDOM 3

#define A  2
#define B  3
#define C  4
#define D  5
#define E  6
#define FF  7
#define G  8
#define H  9

int currentMode = MODES_ALL_ON;

int brainsPin = A2;

void loop()
{   
  currentMode = analogRead(brainsPin);

  switch(currentMode)
  {
    case 0:
    {
         currentMode = MODES_ALL_ON;
         Serial.println(currentMode);
         break;
    } 
    case 1023:
    {
      currentMode = MODES_MOTION_DETECTED;
      Serial.println(currentMode);
      
      break;
    }
    case 300:
    {
      currentMode = MODES_RANDOM;
    }
    default:
    {
        Serial.println(currentMode);
    }
  }
  
  switch(currentMode)
  {
    case MODES_ALL_ON:
    {
      allOn();
      break;
    }
    case MODES_MOTION_DETECTED:
    {
      stepThrough();
      break;
    }
    case MODES_RANDOM:
    {
      randomly();
    }
    default:
    {
      allOn();
    }
  }
}

void allOn()
{

     digitalWrite(A, HIGH); 
     digitalWrite(B, HIGH); 
     digitalWrite(C, HIGH); 
     digitalWrite(D, HIGH); 
     digitalWrite(E, HIGH); 
     digitalWrite(FF, HIGH); 
     digitalWrite(G, HIGH); 
     digitalWrite(H, HIGH);    
}

void setAll(int mode)
{

     digitalWrite(A, HIGH); 
     digitalWrite(B, HIGH); 
     digitalWrite(C, HIGH); 
     digitalWrite(D, HIGH); 
     digitalWrite(E, HIGH); 
     digitalWrite(FF, HIGH); 
     digitalWrite(G, HIGH); 
     digitalWrite(H, HIGH);    
}

void setup() 
{
  pinMode(A0, INPUT);
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

void randomly()
{
  int x;
  
  // Step through all eight EL channels (pins 2 through 9)
  for (x=2; x<=9; x++)
  {
    int state = random(2);
    if(state == 0)
    {
      state = LOW;
    }
    else
    {
      state = HIGHT
    }
    
    digitalWrite(x, state);   // turn the EL channel on
  }
  
  delay(100);              // wait for 1/10 second
  
}

void stepThrough()
{
  int x,status;
  
  // Step through all eight EL channels (pins 2 through 9)
  for (x=2; x<=9; x++)
  {
    digitalWrite(x, HIGH);   // turn the EL channel on
    delay(100);              // wait for 1/10 second
    digitalWrite(x, LOW);    // turn the EL channel off

    digitalWrite(10, status);   // blink both status LEDs
    digitalWrite(13, status);
    status = !status; 
  }  
  
}
