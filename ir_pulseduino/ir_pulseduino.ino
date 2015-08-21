/*
 Fading
 
 This example shows how to fade an LED using the analogWrite() function.
 
 The circuit:
 * LED attached from digital pin 9 to ground.
 
 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe
 
 http://arduino.cc/en/Tutorial/Fading
 
 This example code is in the public domain.
 
 */


int ledPin = 9;    // LED connected to digital pin 9

void setup()  { 
  pinMode(ledPin, OUTPUT); 
} 

void loop()  { 
  for(char i=0; i<48;i++){
  for(char i = 0; i<10;i++){
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(6);
    digitalWrite(ledPin, LOW);
    delayMicroseconds(7);
  }
  delayMicroseconds(350);
  }
  delay(1000);
}


