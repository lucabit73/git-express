const int greenPin = 6;
const int buttonGreen = 8;
int fade = 0;
int bright = 0;
int fadeAmount = 5;
int howLongToWait = 100;     // Wait this many millis()
int lastTimeItHappened = 0;  // The clock time in millis()
int howLongItsBeen;          // A calculated value
int start_base = 0;
int br_start;
int br_end;
int sign_blink;
int blink_val = 255;


char inData[20]; // Allocate some space for the string
char inChar=-1; // Where to store the character read
byte index = 0; // Index into array; where to store the character
int ledStateGreen = HIGH;         // the current state of the output pin
int buttonStateGreen;             // the current reading from the input pin
int lastButtonStateGreen = LOW;   // the previous reading from the input pin
long lastDebounceTime = 0; 
long debounceDelay = 10;
void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(buttonGreen, INPUT);
  Serial.begin(9600);
  Serial.println("Power ON - GIT EXPRESS");
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
  int readingGreen = digitalRead(buttonGreen);
  
  if (readingGreen != lastButtonStateGreen) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (readingGreen != buttonStateGreen) {
      buttonStateGreen = readingGreen;

      // only toggle the LED if the new button state is HIGH
      if (buttonStateGreen == HIGH) {
        ledStateGreen = !ledStateGreen;
        
        Serial.println("start");
      }
    }
  }
  

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonStateGreen = readingGreen;
  /*end read button */
  
  if(Comp("start")==0){
    sign_blink = 0;
    start_base = 1;
    lastTimeItHappened = millis();
    //
    bright = 30;    
    br_start = 30;
    br_end = 100;
    howLongToWait = 50;
    fadeAmount = 2;
  }
  
  if(Comp("wait")==0){
    lastTimeItHappened = millis();
    //
    bright = 50;
    br_start = 50;
    br_end = 255;
    fadeAmount = 5;
    howLongToWait = 15;
  }
  
  if(Comp("end")==0){
    start_base = 0;
    sign_blink = 1;
    lastTimeItHappened = millis();
    analogWrite(greenPin, blink_val);
    //
    howLongToWait = 300;
  }
  if(Comp("err")==0){
    start_base = 0;  
    sign_blink = 1;
    lastTimeItHappened = millis();
    analogWrite(greenPin, blink_val);
    //
    howLongToWait = 80;
  }
   
//------------------   
   
  if (start_base == 1){
    howLongItsBeen = millis() - lastTimeItHappened;
    if ( howLongItsBeen >= howLongToWait ) {
      // do it (again)
      analogWrite(greenPin, bright);
      bright = bright + fadeAmount;
      if (bright <= br_start || bright >= br_end) {
        fadeAmount = -fadeAmount ; 
      }
      lastTimeItHappened = millis();
    }
  }
  
  if (sign_blink == 1){
    howLongItsBeen = millis() - lastTimeItHappened;
    if ( howLongItsBeen >= howLongToWait ) {
      blink_val = abs (blink_val-255);
      analogWrite(greenPin, blink_val);
      lastTimeItHappened = millis();
    }
  }
    
}

