
int potPin = 0;   // select the input pin for the potentiometer
int fadePin = 9;   // select the pin for the LED
int blinkingPin = 10;
int val = 0;      // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor, between 0 - 1024
  Serial.println(val);
  analogWrite(fadePin, val/4); // analogWrite can be between 0-255
  digitalWrite(blinkingPin, HIGH);
  delay(val);
  digitalWrite(blinkingPin, LOW);
  delay(val);
}
