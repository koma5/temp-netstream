#include <SoftwareSerial.h>
#include <String.h>

SoftwareSerial GPS = SoftwareSerial(2,3);

void setup()
{
  GPS.begin(4800);
  Serial.begin(4800);

}

void loop()
{
  Serial.write(GPS.read());

}
