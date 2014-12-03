const int greenPin = 7;
const int redPin = 6;
const int buttonGreen = 8;
const int buttonRed = 3;

const int flashPin = 4;

char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character
int ledStateGreen = HIGH;         // the current state of the output pin
int buttonStateGreen;             // the current reading from the input pin
int lastButtonStateGreen = LOW;   // the previous reading from the input pin
int ledStateRed = HIGH;         // the current state of the output pin
int buttonStateRed;             // the current reading from the input pin
int lastButtonStateRed = LOW;
long lastDebounceTime = 0; 
long debounceDelay = 10;
void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(flashPin, OUTPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(buttonRed, INPUT);
  Serial.begin(9600);
  Serial.println("Power ON - MASBOOTH");
}


char Comp(char* This){

  while(Serial.available() > 0) // Don't read unless
    // there you know there is data
  {
    if(index < 19) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    }
  }

  if(strcmp(inData,This)  == 0){
    for(int i=0;i<19;i++){
      inData[i]=0;
    }
    index=0;
    return(0);

  }
  else{
    return(1);


  }
}
    
void loop() {  
    /* read button */  
  int readingRed = digitalRead(buttonRed);
  int readingGreen = digitalRead(buttonGreen);
  
  if (readingRed != lastButtonStateRed) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  if (readingGreen != lastButtonStateGreen) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (readingRed != buttonStateRed) {
      buttonStateRed = readingRed;

      // only toggle the LED if the new button state is HIGH
      if (buttonStateRed == HIGH) {
        ledStateRed = !ledStateRed;
        
        Serial.println("red");
      }
    }
    if (readingGreen != buttonStateGreen) {
      buttonStateGreen = readingGreen;

      // only toggle the LED if the new button state is HIGH
      if (buttonStateGreen == HIGH) {
        ledStateGreen = !ledStateGreen;
        
        Serial.println("green");
      }
    }
  }
  

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonStateRed = readingRed;
  lastButtonStateGreen = readingGreen;
    /*end read button */
    
    
    
    if(Comp("redon")==0){
        digitalWrite(redPin, HIGH);      
    }
    if(Comp("redoff")==0){
        digitalWrite(redPin, LOW);      
    }
  
    
    if(Comp("greenon")==0){
        digitalWrite(greenPin, HIGH);      
    }
    if(Comp("greenoff")==0){
        digitalWrite(greenPin, LOW);      
    }
    
    
    if(Comp("flashon")==0){
        digitalWrite(flashPin, HIGH);      
    }
    if(Comp("flashoff")==0){
        digitalWrite(flashPin, LOW);      
    }
    
}
