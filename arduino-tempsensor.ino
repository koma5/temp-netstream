
//(Ground) ---- (10k-Resister) -------|------- (10k-Thermistor) ---- (+5v)
//                                    |
//                               Analog Pin A0


#include <math.h>
#include <Ethernet.h>
#include <SPI.h>

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot

//converting the rawADC to Celsius
double therminister(int rawADC)
{
  double temp;
  temp = log(((10240000/rawADC) - 10000));
  temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp )) * temp);
  temp = temp - 273.15; // Kelvon to Celsius
  return temp;
}

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 172, 16, 0, 77 };
//byte subnet[] = { 255, 255, 0, 0 };
//byte gateway[] = { 10, 0, 0, 1 };
byte server[] = { 172, 16, 0, 62 }; // runnig server.js

EthernetClient client;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Ethernet.begin(mac, ip);
  delay(1000);
  
  Serial.println("connecting...");
  
  if (client.connect(server, 6667)) {
    Serial.println("connected");
    client.println("Start");
  } else {
    Serial.println("connection failed");
  }
  
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);            
     

  // print the results to the serial monitor:
  //Serial.print("rawADC = " );                       
  //Serial.print(sensorValue);      
  //Serial.print("\tcelsius = " );                       

  if (!client.connected()) {
    client.stop();
    delay(1000);
    Serial.println();
    Serial.println("disconnected - try to reconnect");
    client.connect(server, 6667);
    client.println("Start");  
  }
  else {
    client.println(therminister(sensorValue));
  }

  // print the results to the serial monitor:
  //Serial.print("rawADC = " );                       
  //Serial.print(sensorValue);      
  //Serial.print("\tcelsius = " ); 
  //Serial.print(therminister(sensorValue)); 
  //Serial.print("\r\n" );

  delay(100);                     
}
