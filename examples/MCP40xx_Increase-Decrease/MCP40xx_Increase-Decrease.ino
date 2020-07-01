/*
        MCP4011 Digital Potentiometer from Microchip

        It consist of a volatile, 6-bit digital Pot. Controller by an UP/~DOWN serial interface
        63 taps, Power-on Recall

        ********** LIBRARY TEST *******************

        Model: MCP4011-503 --> 50k Ohms nominal
        Author: Daniel Melendrez
        Code: Increase & Decrease variable resistor --> Wiper connected to A:

              A ----/\/\/\/\/\/\------ B
                    |       /\
                    |________|  (W)     

        Ver: 0.2 - Updated to latest library version. General cleanup
        Date: July 2020
*/

#include <MCP4011.h>
#include <Bounce2.h>    // Debounce chattering using the Library: https://github.com/thomasfredericks/Bounce2

// Pins declaration
const int UDPin = 2;   // Pin 2 is UP/DOWN
const int CSPin = 3;   // Pin 3 is CHIP SELECT
const int pinUp = 9;
const int pinDwn =  8;
const int upLed = 11;
const int dwnLed = 10;

int tapNum;
int analogIn;

float Rx = 0.0;
float pos = 0.0;
float Res;
float elapsed;

Bounce up = Bounce();
Bounce dwn = Bounce();

MCP4011 pot(CSPin, UDPin);

void setup() {

  // Setup and initialize the device
  pot.setup();
  pot.begin();

  pot.zeroWiper();    // Sets the initial value of the Pot to the minimum value possible

  pinMode(pinUp, INPUT_PULLUP);
  pinMode(pinDwn, INPUT_PULLUP);

  // Attach debouncing objects to push-buttons
  up.attach(pinUp);
  dwn.attach(pinDwn);

  // Define the debouncing time 
  up.interval(25);
  dwn.interval(25);

  Serial.begin(115200);

  Serial.println(F("*********************************"));
  Serial.println(F("  MCP4011 Digital Potentiometer "));
  Serial.println(F("        LIBRARY Ver. 0.2         "));
  Serial.println(F("*********************************"));

  pinMode(upLed, OUTPUT);
  pinMode(dwnLed, OUTPUT);

  delay(500);

}

void loop() {

  // Read button status
  if (up.update()) {
    if (up.fell()) {

      increaseValue();

      readPotData();
      printRetrievedData();

    }
  } else{
    digitalWrite(upLed, LOW);
  }

  // Read button status
  if (dwn.update()) {
    if (dwn.fell()) {

      decreaseValue();

      readPotData();
      printRetrievedData();

    }
  } else{
    digitalWrite(dwnLed, LOW);
  }

}

// Resistance increase routine
void increaseValue(){

      digitalWrite(upLed, HIGH);

      pot.inc();      // Increase one tap

}

// Resistance decrease routine
void decreaseValue(){

      digitalWrite(dwnLed, HIGH);

      pot.dec();      // Decrease one tap

}

void readPotData(){

 // Retrieve Pot data
      tapNum = pot.taps();
      pos = pot.wiper();
      Res = pot.readValue();
      elapsed = pot.decMicros();

}

void printRetrievedData(){

      // Print potentiometer data on serial port
      Serial.println(F("*********************************"));
      Serial.print("Tap: ");
      Serial.println(tapNum);

      Serial.print(F("Resistance (approx): "));
      Serial.print(Res / 1000, 3);

      Serial.println(F(" kOhms;"));

      Serial.print(F("Wiper[%]: "));
      Serial.println(pos * 100, 2);

      Serial.print(F("Decrement time: "));
      Serial.print(elapsed);
      Serial.println(F(" us"));
      Serial.println(F("*********************************"));

}