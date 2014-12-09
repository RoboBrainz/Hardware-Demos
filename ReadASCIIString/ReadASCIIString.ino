/*
  Reading a serial ASCII-encoded string.
 
 This sketch demonstrates the Serial parseInt() function.
 It looks for an ASCII string of comma-separated values.
 It parses them into ints, and uses those to fade an RGB LED.
 
 Circuit: Common-anode RGB LED wired like so:
 * Red cathode: digital pin 3
 * Green cathode: digital pin 5
 * blue cathode: digital pin 6
 * anode: +5V
 
 created 13 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
 */

// pins for the LEDs:
//const int redPin = 3;
//const int greenPin = 5;
//const int bluePin = 6;

#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  strip.begin();
  strip.show();
  // Initialize all pixels to 'off'
  // make the pins outputs:
  //pinMode(redPin, OUTPUT); 
  //pinMode(greenPin, OUTPUT); 
  //pinMode(bluePin, OUTPUT); 
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int red = Serial.parseInt(); 
    // do it again:
    int green = Serial.parseInt(); 
    // do it again:
    int blue = Serial.parseInt(); 

    // look for the newline. That's the end of your
    // sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      // fade the red, green, and blue legs of the LED: 
      //analogWrite(redPin, red);
      //analogWrite(greenPin, green);
      //analogWrite(bluePin, blue);
      strip.setPixelColor(1, strip.getPixelColor(0));
      strip.setPixelColor(0, strip.Color(red, green, blue));
      strip.show();

      // print the three numbers in one string as hexadecimal:
      if (red < 16)
        Serial.print('0'); // pad if red will show just one hexadecimal digit
      Serial.print(red, HEX);
      if (green < 16)
        Serial.print('0'); // and similar
      Serial.print(green, HEX);
      if (blue < 16)
        Serial.print('0'); // similar here too
      Serial.println(blue, HEX);
    }
  }
}








