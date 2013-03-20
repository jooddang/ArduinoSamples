
int lightPin = 0;   // select the input pin for the potentiometer
int motorPin = 9; // select the pin for the Motor
int val = 0;      // variable to store the value coming from the sensor
int prevVal = 0;
int BOUNDARY = 800;

int aPin = 11;
int bPin = 12;
int cPin = 13;
int speakerOut = 7;               
byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
byte ringA[] =   "ceggggppggppgppCCCCCpppppp";
int count = 0;
int count2 = 0;
int count3 = 0;

void setup() {
  Serial.begin(9600);
 pinMode(aPin, OUTPUT); 
 pinMode(bPin, OUTPUT); 
 pinMode(cPin, OUTPUT); 
 pinMode(speakerOut, OUTPUT);
}
void loop() {
  val = analogRead(lightPin);    // read the value from the sensor, between 0 - 1024
  Serial.println(val);
  if (val < BOUNDARY) {
    analogWrite(motorPin, 100); // analogWrite can be between 0-255
  }
  else {
    analogWrite(motorPin, 0);
  }
  
  if (prevVal < BOUNDARY && val > BOUNDARY) {
    playA();
  }
  prevVal = val;
}



void playA() {

  digitalWrite(cPin, HIGH);
  digitalWrite(bPin, HIGH);
  digitalWrite(aPin, HIGH);
  Serial.println("play A");
  
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
  digitalWrite(bPin, LOW);
  digitalWrite(cPin, LOW);
}
