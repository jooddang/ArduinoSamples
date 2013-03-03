int redPin = 9;
int greenPin = 10;
int bluePin = 11;

char serialString[100];

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
  analogWrite(redPin, 1);
  analogWrite(greenPin, 1);
  analogWrite(bluePin, 1);
  Serial.println("What time do you want to sail?(e.g. 10:00, 13:00, 18:00, ...) :");
}

int compareWords(char* w1, char *w2) {

  if (strcmp(w1, w2) == 0) {
    return 1;
  }
  
  return 0;
}

void turnOnLED(int redCount, int greenCount, int blueCount) {
  
  analogWrite(redPin, redCount * 0.1 * 255);
  analogWrite(greenPin, greenCount * 0.1 * 255);
  analogWrite(bluePin, blueCount * 0.1 * 255);
  
}

void loop() {
  
  readSerialString(serialString);
  
  if (serialString[0] != 0) {
    Serial.println(serialString);
  }

  for (int i = 0; i < 100; i++) {
    
    if (serialString[i] == ':') {// || serialString[i] == 0) {

      char buf[10];
      memset (buf, 0, sizeof(buf));

      for (int k = 0; k < i; k++) {
        buf[k] = serialString[k];
      }

      int time = atoi(buf);
      Serial.println(time);
      
      if (time < 7)
        turnOnLED(0,0,1);
      if (time == 7)
        turnOnLED(9,0,4);
      if (time == 8)
        turnOnLED(6,0,2);
      if (time == 9)
        turnOnLED(5,0,4);
      if (time == 10)
        turnOnLED(1,2,8);
      if (time == 11)
        turnOnLED(0,3,9);
      if (time == 12)
        turnOnLED(0,2,10);
      if (time > 12 && time < 17)
        turnOnLED(0,3,10);
      if (time == 17)
        turnOnLED(4,0,6);
      if (time == 18)
        turnOnLED(7,0,4);
      if (time == 19)
        turnOnLED(7,0,3);
      if (time == 20)
        turnOnLED(9,0,5);
      if (time == 21)
        turnOnLED(9,0,6);
      if (time > 21)
        turnOnLED(0,0,1);
    }
  }
  
  Serial.println("What time do you want to sail?(e.g. 10:00, 13:00, 18:00, ...) :");
  
  for (int i = 0; i < 100; i++) {
    serialString[i] = 0;
  }
  
  delay(2000);
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

