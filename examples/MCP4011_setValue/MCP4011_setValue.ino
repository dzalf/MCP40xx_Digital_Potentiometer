/*
        MCP4011 Digital Potentiomenter from Microchip

        It consist of a volatile, 6-bit digital Pot. Contreoller by an UP/~DOWN serial interface
        63 taps, Power-on Recall

        ********** LIBRARY TEST *******************

        Model: MCP4011-503 --> 50k Ohms nominal
        Code: Set the value via the serial port
        Author: Daniel Melendrez

        Ver: 0.1
        Date: March 2020
*/

#include <MCP4011.h>

// Pins declaration
const int UDPin = 2;   // Pin 2 is UP/DOWN
const int CSPin = 3;   // Pin 3 is CHIP SELECT

int tapNum;

float Rx = 0.0;   // Holds the desired Resistor value
float pos = 0;
float Res;
float del;

byte target;

bool serialFinished = false;

String serialData = "";   // I know, I know. Serials are "evil" but what do you want from me?

MCP4011 pot(CSPin, UDPin);

void setup() {

  pot.setup();
  pot.begin();

  pot.zeroWiper();

  Serial.begin(115200);

  Serial.println(F("*********************************"));
  Serial.println(F("  MCP4011 Digital Potentiometer "));
  Serial.println(F("        LIBRARY ver 0.1        "));
  Serial.println(F("*********************************"));

  delay(500);

}

void loop() {

  if (serialFinished) {

    serialFinished = false;

    Rx = serialData.toFloat();

    if ((Rx >= 0.0) && (Rx <= NOMINAL_RESISTANCE)) {

      target = pot.setValue(Rx);

      Res = pot.readValue();

      tapNum = pot.taps();

      Serial.println(F("**********************"));

      Serial.print(F("Desired Resistance: "));
      Serial.println(Rx, 2);

      Serial.print(F("Current Resistance: "));
      Serial.println(Res, 2);

      Serial.print(F("Target Tap: "));
      Serial.println(target);

      Serial.print(F("Current Tap: "));
      Serial.println(tapNum);

      Serial.println(F("**********************"));

      serialData = "";

    }

  }

}

// Serial string management
void serialEvent() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      serialData += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      // clear the string for new input:
      serialFinished = true;
    }
  }

}