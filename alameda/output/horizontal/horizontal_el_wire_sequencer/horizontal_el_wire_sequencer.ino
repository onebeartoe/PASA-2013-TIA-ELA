

#define MODES_ALL_ON 1
#define MODES_STEP_THROUGH 2

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
//  if (Serial.available())
//  {
//    currentMode = Serial.read() - '0';
//  }
  
  currentMode = analogRead(brainsPin);

  switch(currentMode)
  {
    case 0:
    {
         Serial.println(currentMode);
         break;
    } 
    case 1023:
    {
         Serial.println(currentMode);
      break;
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
    case MODES_STEP_THROUGH:
    {
      stepThrough();
      break;
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

void setup() 
{
  pinMode(A0, INPUT);


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
