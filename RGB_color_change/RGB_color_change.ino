int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int redCount = 0;
int greenCount = 0;
int blueCount = 0;
  
char serialString[100];


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  analogWrite(redPin, 127);
  analogWrite(greenPin, 127);
  analogWrite(bluePin, 127);
  Serial.println("enter color command (e.g.: 'rrrggbbb') I MUST NOT exceed 100 characters. :");
}

void loop() {
  
  readSerialString(serialString);
  
  char colorCharacter;
  
  if (serialString[0] != 0) {
    redCount = 0;
    greenCount = 0;
    blueCount = 0;
  }
  
  for (int i = 0; i < 100; i++) {
    colorCharacter = serialString[i];
    
    if (colorCharacter == 'r') {
      redCount++;
    }
    else if (colorCharacter == 'g') {
      greenCount++;
    }
    else if (colorCharacter == 'b') {
      blueCount++;
    }
    else if (colorCharacter == 0) {
      break;
    }
  }
  
  redCount = redCount % 11;
  greenCount = greenCount % 11;
  blueCount = blueCount % 11;
  
  Serial.print("red: ");
  Serial.print(redCount * 10);
  Serial.print("%, green: ");
  Serial.print(greenCount * 10);
  Serial.print("%, blue: ");
  Serial.print(blueCount * 10);
  Serial.println("%");
  Serial.println("enter color command (e.g.: 'rrrggbbb') I MUST NOT exceed 100 characters. :");
  
  analogWrite(redPin, redCount * 0.1 * 255);
  analogWrite(greenPin, greenCount * 0.1 * 255);
  analogWrite(bluePin, blueCount * 0.1 * 255);
  
  for (int i = 0; i < 100; i++) {
    serialString[i] = 0;
  }
  
  delay(1000);
  
  /*
  // fade in  
  for (int i = 0; i < 256; i+=5) {
    int sec = random(10);
    sec = sec * 1000;
    
    analogWrite(redPin, i);
    analogWrite(greenPin, sec);
    analogWrite(bluePin,255-i);
    delay(30);
  }
  
  // fade out
  for (int i = 255; i >= 0; i-=5) {
    int sec = random(10);
    sec = sec * 1000;
    
    analogWrite(redPin, i);
    analogWrite(greenPin, sec);
    analogWrite(bluePin,255-i);
    delay(30);
  }
  */
}

void readSerialString (char *strArray) {
  int i = 0;
  if(!Serial.available()) {
    return;
  }
  while (Serial.available()) {
    strArray[i] = Serial.read();
    i++;
  }
}

