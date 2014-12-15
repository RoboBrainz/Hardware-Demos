#include <SoftwareSerial.h>

const int redPin = 0;
const int bluePin = 1;
const int greenPin = 2;

const int outRx = 0;
const int outTx = 1;

SoftwareSerial toOtherArduino(outTx, outRx);

void setup()
{
  //Serial.begin(9600);
  toOtherArduino.begin(9600);
}

void loop()
{
  float r = (float)analogRead(redPin)+1.0;
  float g = (float)analogRead(greenPin)+1.0;
  float b = (float)analogRead(bluePin)+1.0;
    
  int true_r = (int)((r/1024.0)*255.0);
  int true_g = (int)((g/1024.0)*255.0);
  int true_b = (int)((b/1024.0)*255.0);
  //while(Serial.available() > 0) {
 /*   Serial.print(true_r);
    Serial.print(' ');
    Serial.print(true_g);
    Serial.print(' ');
    Serial.println(true_b);*/
  toOtherArduino.print(true_r);
  toOtherArduino.print(' ');
  toOtherArduino.print(true_g);
  toOtherArduino.print(' ');
  toOtherArduino.println(true_b);
  delay(1000);
  //}
}
