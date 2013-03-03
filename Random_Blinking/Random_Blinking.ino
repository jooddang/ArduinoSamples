int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  
  for (int i = 0; i < 10; i++) {
    
    int sec = random(10);
    sec = sec * 1000;
    
    digitalWrite(ledPin, HIGH);
    delay(sec);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
}
