/*
 * Servo Control Serial
 * modified for TUI October 2007
 * Servo Serial Better
 * -------------------
 *
 * Created 18 October 2006
 * copyleft 2006 Tod E. Kurt <tod@todbot.com>
 * http://todbot.com/
 *
 * adapted from "http://itp.nyu.edu/physcomp/Labs/Servo"
 */

int servoPin = 7;      // Control pin for servo motor
int servoPin2 = 8;
int fsrPin = 0;

int pulseWidth = 0;    // Amount to pulse the servo
int pulseWidth2 = 0;
long lastPulse = 0;    // the time in millisecs of the last pulse
int refreshTime = 100;  // the time in millisecs needed in between pulses
int val;               // variable used to store data from serial port
int val2;

int minPulse = 500;   // minimum pulse width
int maxPulse = 2250;  // maximum pulse width

int prevChecksum = 0;

void setup() {
  pinMode(servoPin, OUTPUT);  // Set servo pin as an output pin
  pinMode(servoPin2, OUTPUT);
  pulseWidth = minPulse;      // Set the motor position to the minimum
  pulseWidth2 = maxPulse;
  Serial.begin(9600);         // connect to the serial port
  Serial.println("Servo control program ready");
}

void loop() {
//  val = Serial.read();      // read the serial port
  int checkSum = analogRead(fsrPin);
//  if (val >= '1' && val <= '9' ) {
  if (checkSum < 50 && prevChecksum > 50) {
    val = val - '0';        // convert val from character variable to number variable
    val = val - 1;          // make val go from 0-8
    if (pulseWidth > 2000) {
      val = 0;
      val2 = 8;
    }
    else {
      val = 8;
      val2 = 0;
    }
    pulseWidth = (val * (maxPulse-minPulse) / 8) + minPulse;  // convert val to microseconds
    pulseWidth2 = (val2 * (maxPulse-minPulse) / 8) + minPulse;  // convert val to microseconds
    Serial.print("Moving servo to position ");
    Serial.println(pulseWidth,DEC);
  }
  updateServo();   // update servo position
  prevChecksum = checkSum;
}

// called every loop(). 
// uses global variables servoPi, pulsewidth, lastPulse, & refreshTime
void updateServo() {
  // pulse the servo again if rhe refresh time (20 ms) have passed:
  if (millis() - lastPulse >= refreshTime) {
    digitalWrite(servoPin, HIGH);   // Turn the motor on
    digitalWrite(servoPin2, HIGH);
    delayMicroseconds(pulseWidth);  // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);    // Turn the motor off
    digitalWrite(servoPin2, LOW);
    lastPulse = millis();           // save the time of the last pulse
  }
}


