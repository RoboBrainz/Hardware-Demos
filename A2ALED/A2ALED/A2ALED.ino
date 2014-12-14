// Drew Johnson & C. Joan C. Paraiso
// Other Arduino+LED Demo - LED CKT
// 14 December 2014
// Project Robobrainz
// Pacific Lutheran University

#include <SoftwareSerial.h>  
#include <Adafruit_NeoPixel.h>

const int neoPixelPin = 6;  // neoPixel LED data input pin, Arduino D6
const int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
const int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(2, neoPixelPin, NEO_RGB + NEO_KHZ800);

void setup()
{
  //Setup Code by: Jim Lindblom, Sparkfun Electronics
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  //bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  //bluetooth.print("$$$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  //bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  
  //NeoPixel Setup
  strip.begin();
  strip.show();
}

void loop()
{
  while (bluetooth.available() > 0)  // While something was sent from bluetooth
  {
    Serial.println("BEGIN"); // print statement for debug

    // look for the next valid integer in the incoming serial stream:
    int red = bluetooth.parseInt();
   Serial.println(red); 
    // do it again:
    int green = bluetooth.parseInt();
   Serial.println(green); 
    // do it again:
    int blue = bluetooth.parseInt();
   Serial.println(blue);

    // look for the newline. That's the end of your sentence:
    int lineEnd = (int)bluetooth.read(); // handle line-end
    if (lineEnd == '\r') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);
      
      // fade the red, green, and blue legs of the LED: 
      strip.setPixelColor(1, strip.getPixelColor(0));
      strip.setPixelColor(0, strip.Color(red, green, blue));
      strip.show();
  
      // print the three numbers in one string as hexadecimal:
      if (red < 16)
        bluetooth.print('0'); // pad if red will show just one hexadecimal digit
      bluetooth.print(red, HEX);
      if (green < 16)
        bluetooth.print('0'); // and similar
      bluetooth.print(green, HEX);
      if (blue < 16)
        bluetooth.print('0'); // similar here too
      bluetooth.println(blue, HEX);
    }
  }
}
