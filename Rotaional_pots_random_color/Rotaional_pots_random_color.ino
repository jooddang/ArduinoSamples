
// Analog pin settings
int aIn = 0;    // Potentiometers connected to analog pins 0, 1, and 2
int bIn = 1;    //   (Connect power to 5V and ground to analog ground)
int cIn = 2;  

// Digital pin settings
int aOut = 9;   // LEDs connected to digital pins 9, 10 and 11
int bOut = 10;  //   (Connect cathodes to digital ground)
int cOut = 11;  

// Values
int aVal = 0;   // Variables to store the input from the potentiometers
int bVal = 0;  
int cVal = 0;

// Answer value
int aAnswer = 0;
int bAnswer = 0;
int cAnswer = 0;

int aAnswerFlag = 0;
int bAnswerFlag = 0;
int cAnswerFlag = 0;

// Variables for comparing values between loops
int wait = (1000);    // Delay between most recent pot adjustment and output

int checkSum     = 0; // Aggregate pot values
int prevCheckSum = 0;
int sens         = 1; // Sensitivity theshold, to prevent small changes in 
                      // pot values from triggering false reporting
// FLAGS
int PRINT = 1; // Set to 1 to output values
int DEBUG = 0; // Set to 1 to turn on debugging output
int SUCCESS = 1; // Set to 1 if succeed to find the brightness

void setup()
{
  pinMode(aOut, OUTPUT);   // sets the digital pins as output
  pinMode(bOut, OUTPUT);   
  pinMode(cOut, OUTPUT); 
  Serial.begin(9600);     // Open serial communication for reporting
}

void loop()
{
  if (SUCCESS == 1) {
    aAnswer = random(256);
    bAnswer = random(256);
    cAnswer = random(256);
    Serial.print("[");
    Serial.print(aAnswer);
    Serial.print("]");
    Serial.print("[");
    Serial.print(bAnswer);
    Serial.print("]");
    Serial.print("[");
    Serial.print(cAnswer);
    Serial.println("]");
    
    SUCCESS = 0;
  }
  
  aVal = analogRead(aIn) / 4;  // read input pins, convert to 0-255 scale
  bVal = analogRead(bIn) / 4; 
  cVal = analogRead(cIn) / 4;  

//    Serial.print("1111[");
//    Serial.print(aVal);
//    Serial.print("]");
//    Serial.print("[");
//    Serial.print(bVal);
//    Serial.print("]");
//    Serial.print("[");
//    Serial.print(cVal);
//    Serial.println("]");

//  analogWrite(aOut, aVal);    // Send new values to LEDs
//  analogWrite(bOut, bVal);
//  analogWrite(cOut, cVal);

    checkSum = aVal+bVal+cVal;      // ...add up the 3 values.
    if ( abs(checkSum - prevCheckSum) > sens )   // If old and new values differ above sensitivity threshold
    {
      if (aVal < aAnswer + 5 && aVal > aAnswer - 5) {
        analogWrite(aOut, 255);
        aAnswerFlag = 1;
      }
      else {
        for (int i = 0; i < 5; i++) {
          int diff = abs(aVal - aAnswer);
          analogWrite(aOut, 255);
          delay(diff);
          analogWrite(aOut, 0);
          delay(diff);
        }
      }
      
      if (bVal < bAnswer + 5 && bVal > bAnswer - 5) {
        analogWrite(bOut, 255);
        bAnswerFlag = 1;
      }
      else {
        bAnswerFlag = 0;
        for (int i = 0; i < 5; i++) {
          int diff = abs(bVal - bAnswer);
          analogWrite(bOut, 255);
          delay(diff);
          analogWrite(bOut, 0);
          delay(diff);
        }
      }
      
      if (cVal < cAnswer + 5 && cVal > cAnswer - 5) {
        analogWrite(cOut, 255);
        cAnswerFlag = 1;
      }
      else {
        cAnswerFlag = 0;
        for (int i = 0; i < 5; i++) {
          int diff = abs(cVal - cAnswer);
          analogWrite(cOut, 255);
          delay(diff);
          analogWrite(cOut, 0);
          delay(diff);
        }
      }
      
      if (PRINT)                    // ...and if the PRINT flag is set...
      {
        Serial.print("A: ");        // ...then print the values.
        Serial.print(aVal);         
        Serial.print("\t"); 
        Serial.print("B: ");        
        Serial.print(bVal);
        Serial.print("\t");
        Serial.print("C: ");                
        Serial.println(cVal); 
        PRINT = 0;
      }  
    }
    else
    {
      PRINT = 1;  // Re-set the flag   
    } 
    prevCheckSum = checkSum;  // Update the values




    if (DEBUG)   // If we want debugging output as well...
    {
      Serial.print(checkSum);
      Serial.print("<=>");
      Serial.print(prevCheckSum);
      Serial.print("\tPrint: ");
      Serial.println(PRINT);
    }

}

