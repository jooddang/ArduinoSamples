
int aPin = 11;
int bPin = 12;
int cPin = 13;
int speakerOut = 7;               
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte default_melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";
byte noise[] =  "aagfcbbbpppppp";
byte ringA[] =   "ddddcccccccpppccceeegggCCCCbbbbbaaaaaaaaaaaaaappppaaaaagggfffeeeddddfffffeeeeeeeeepppdddccccceeedddddddddddddcccccceeeeeeeeepppppp";
byte ringB[] =  "cccddeeeccccdddeeeedddcccdddeeeffffdddeeefffeeeddddeeefffgggggeeeegggaaagggeeddccccdddeeffgggeeedddddpppppp";
byte ringC[] =  "pccccdddeeddddddddeeeddddcccddeedddddfffeeedddcccddddeeeddddddeedddddddddccccppppp";
// count length: 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0
//                                10                  20                  30
int count = 0;
int count2 = 0;
int count3 = 0;
int MAX_COUNT = 24;
int statePin = LOW;

// analog rotaional pot
int potin = 0;
int potval = 0;
int checkSum     = 0; // Aggregate pot values
int prevCheckSum = 0;
int sens = 1;

int forcePin = 4;  // select the input pin for the sensor
boolean forceval = false;

void setup() {
 pinMode(aPin, OUTPUT); 
 pinMode(bPin, OUTPUT); 
 pinMode(cPin, OUTPUT); 
 pinMode(speakerOut, OUTPUT);
 Serial.begin(9600);
}

void playA() {

  digitalWrite(cPin, LOW);
  digitalWrite(bPin, LOW);
  digitalWrite(aPin, HIGH);
  for (count = 0; count < sizeof(ringA); count++) {

//    statePin = !statePin;
    
    for (count2=0;count2<8;count2++) {
      if (names[count2] == ringA[count]) {
        for( int i=0; i<50; i++ ) {   // play it for 50 cycles
          digitalWrite(speakerOut,HIGH);
          delayMicroseconds(tones[count2]);
          digitalWrite(speakerOut, LOW);
          delayMicroseconds(tones[count2]);
        }
      } 
      if (ringA[count] == 'p') {
        // make a pause of a certain size
        digitalWrite(speakerOut, 0);
        delayMicroseconds(500);
      }
    }
  }
  digitalWrite(aPin, LOW);
}

void playB() {

  digitalWrite(aPin, LOW);
  digitalWrite(cPin, LOW);
  digitalWrite(bPin, HIGH);
  for (count = 0; count < sizeof(ringB); count++) {
    
    for (count2=0;count2<8;count2++) {
      if (names[count2] == ringB[count]) {
        for( int i=0; i<50; i++ ) {   // play it for 50 cycles
          digitalWrite(speakerOut,HIGH);
          delayMicroseconds(tones[count2]);
          digitalWrite(speakerOut, LOW);
          delayMicroseconds(tones[count2]);
        }
      } 
      if (ringB[count] == 'p') {
        // make a pause of a certain size
        digitalWrite(speakerOut, 0);
        delayMicroseconds(500);
      }
    }
  }
  digitalWrite(bPin, LOW);
}

void playC() {

  digitalWrite(aPin, LOW);
  digitalWrite(bPin, LOW);
  digitalWrite(cPin, HIGH);
  for (count = 0; count < sizeof(ringC); count++) {

    for (count2=0;count2<8;count2++) {
      if (names[count2] == ringC[count]) {
        for( int i=0; i<50; i++ ) {   // play it for 50 cycles
          digitalWrite(speakerOut,HIGH);
          delayMicroseconds(tones[count2]);
          digitalWrite(speakerOut, LOW);
          delayMicroseconds(tones[count2]);
        }
      } 
      if (ringC[count] == 'p') {
        // make a pause of a certain size
        digitalWrite(speakerOut, 0);
        delayMicroseconds(500);
      }
    }
  }
  digitalWrite(cPin, LOW);
}


void playNoise() {

  for (count = 0; count < sizeof(noise); count++) {
    
    statePin = !statePin;
    digitalWrite(aPin, statePin);
    digitalWrite(bPin, !statePin);
    digitalWrite(cPin, !statePin);
    
    for (count2=0;count2<8;count2++) {
      if (names[count2] == noise[count]) {
        for( int i=0; i<50; i++ ) {   // play it for 50 cycles
          digitalWrite(speakerOut,HIGH);
          delayMicroseconds(tones[count2]);
          digitalWrite(speakerOut, LOW);
          delayMicroseconds(tones[count2]);
        }
      } 
      if (noise[count] == 'p') {
        // make a pause of a certain size
        digitalWrite(speakerOut, 0);
        delayMicroseconds(500);
      }
    }
  }
}

void loop() {
  digitalWrite(speakerOut, LOW);     
  potval = analogRead(potin) / 4; // read pot value
//  checkSum = potval;
//    Serial.print("check : ");
//    Serial.print(abs(checkSum - prevCheckSum));
//  if (abs(checkSum - prevCheckSum) >= sens) {
    
//    Serial.print("check : ");
//    Serial.print(potval);
  checkSum = analogRead(forcePin);
  Serial.print(prevCheckSum);
  Serial.print("  ");
  Serial.println(checkSum);
  if (checkSum < 50 && prevCheckSum > 50) {
    if (forceval == true) {
      forceval = false;
    }
    else {
      forceval = true;
    }
  }

  if (forceval == true) {
    if (potval > 50 && potval < 60) {
      playA();
    }
    else if (potval > 120 && potval < 130) {
      playB();
    }
    else if (potval >200 && potval < 210) {
      playC();
    }
    else {
      playNoise();
    }
//  }
  }
  prevCheckSum = checkSum;
}

