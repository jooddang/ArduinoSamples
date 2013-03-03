#include <SoftwareSerial.h>

/*
 * Resistive Sensor Input
 * Takes the input from a resistive sensor, e.g., FSR or photocell
 * Dims the LED accordingly, and sends the value (0-255) to the serial port
 */

int photoPin = 0;
int forcePin = 1;  // select the input pin for the sensor
int ledPin = 11;    // select the output pin for the LED
int photoval = 0;
int forceval = 0;        // variable to store the value coming from the sensor
//SoftwareSerial forceSerial(0,1);

void setup() {
  Serial.begin(9600);
//  forceSerial.begin(14400);
}

void loop() {
  photoval = analogRead(photoPin);
//  forceval = analogRead(forcePin); // read the value from the sensor, 0-1023
//  analogWrite(ledPin, val/4);  // analogWrite (dimming the LED) can be between 0-255
  Serial.println(photoval/2);       // writing the value to the PC via serial connection 
//  forceSerial.println(forceval/4);
  delay(50);                   // rest a little...
}
