int steeringWheelPin = A0;
int paddlesPin = A1;
int leftButtonPin = 4;
int rightButtonPin = 5;
int upButtonPin = 2;
int downButtonPin = 3;

char lastSteering = 'g';
char currentDirection = 'g';
char currentSteering = 'g';
char lastDirection = 'g';
char lastOrder = 'g';
unsigned long  rightButtonTime;
unsigned long  leftButtonTime;
unsigned long  upButtonTime;
unsigned long  downButtonTime;
unsigned long  wheelButtonsTime;

void setup() 
{
  Serial.begin(9600);
  
  //Set the button pins as input
  pinMode(leftButtonPin, INPUT);  
  pinMode(rightButtonPin, INPUT);  
  pinMode(upButtonPin, INPUT);  
  pinMode(downButtonPin, INPUT);
  //Activate the pull-ups
  digitalWrite(leftButtonPin, HIGH);  
  digitalWrite(rightButtonPin, HIGH);  
  digitalWrite(upButtonPin, HIGH);  
  digitalWrite(downButtonPin, HIGH);  
}


void loop() 
{
  //debug();
  updateState();
  
  delay(100);
}

void updateState()
{
  char thisDirection;
  char thisSteering;
  
  switch(paddles())
  {
    case -1:
      thisDirection = 's';
      break;
    case 0:
      thisDirection = 'p';
      break;
    case 1:
      thisDirection = 'w';
      break;
    default:
      thisDirection = 'p';
      break;
  }

  if(thisDirection != lastDirection)
  {
    //Serial.println(thisDirection);
    sendOrder(thisDirection);
  }
  
  lastDirection = thisDirection;

  switch(steeringWheel())
  {
    case -1:
      thisSteering = 'd';
      break;
    case 0:
      thisSteering = lastDirection;
      break;
    case 1:
      thisSteering = 'a';
      break;
    default:
      thisSteering = lastDirection;
      break;
  }
  
  if(thisSteering != lastSteering)
  {
    //Serial.println(thisSteering);
    sendOrder(thisSteering);
  }
  
  lastSteering = thisSteering;
  
  
  if(rightButton() == 0 && leftButton() == 0)
  {
    if(millis()>wheelButtonsTime)
    {
      Serial.println('f');
      wheelButtonsTime = millis()+2000;
    }
    rightButtonTime = millis()+500;
    leftButtonTime = millis()+500;
  }  
  else if(rightButton() == 0 && millis()>rightButtonTime)
  {
    Serial.println('u');
    rightButtonTime = millis()+500;
  }  
  else if(leftButton() == 0 && millis()>leftButtonTime)
  {
    Serial.println('j');
    leftButtonTime = millis()+500;
  }
  
  if(upButton() == 0 && millis()>upButtonTime)
  {
    Serial.println('+');
    upButtonTime = millis()+200;
  }
  
  if(downButton() == 0 && millis()>downButtonTime)
  {
    Serial.println('-');
    downButtonTime = millis()+200;
  }
}

void sendOrder(char order)
{
  if(order != lastOrder)// && order != '')
  {
    Serial.println(order);
  }
  
  lastOrder = order;
}

void debug()
{
  Serial.print("Steering: ");
  Serial.print(steeringWheel());
  Serial.print(" Paddles: ");
  Serial.print(paddles());
  Serial.print(" Buttons: ");
  Serial.print(" Left: ");
  Serial.print(leftButton());
  Serial.print(" Right: ");
  Serial.print(rightButton());
  Serial.print(" Up: ");
  Serial.print(upButton());
  Serial.print(" Down: ");
  Serial.println(downButton());
}

int steeringWheel()
{
  int centerValue = 400;
  int threshold = 50;
  
  int readValue = analogRead(steeringWheelPin);
  int value = 0;
  
  if(readValue < (centerValue - threshold))
    value = -1;
  else if(readValue > (centerValue - threshold) && readValue < (centerValue + threshold))
    value = 0;
  else if(readValue > (centerValue + threshold))
    value = 1;

  delay(1);        // delay in between reads for stability
  
  return value;
}

int paddles()
{
  int centerValue = 30;
  int threshold = 5;
  
  int readValue = analogRead(paddlesPin);
  int value = 0;
  
  if(readValue < (centerValue - threshold))
    value = -1;
  else if(readValue > (centerValue - threshold) && readValue < (centerValue + threshold))
    value = 0;
  else if(readValue > (centerValue + threshold))
    value = 1;

  delay(1);        // delay in between reads for stability
  
  return value;
}

int leftButton()
{
  int value = digitalRead(leftButtonPin);
  delay(1);        // delay in between reads for stability
  
  return value;
}

int rightButton()
{
  int value = digitalRead(rightButtonPin);
  delay(1);        // delay in between reads for stability
  
  return value;
}

int upButton()
{
  int value = digitalRead(upButtonPin);
  delay(1);        // delay in between reads for stability
  
  return value;
}

int downButton()
{
  int value = digitalRead(downButtonPin);
  delay(1);        // delay in between reads for stability
  
  return value;
}
