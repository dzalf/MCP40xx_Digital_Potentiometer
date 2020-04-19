
/*
    Microchip 64 taps Single Digital Potentiometer
    Simple two-wire UP/DOWN interface
    Author: Daniel Melendrez
    Date: March 2020 (COVID-19 Vibes)
    Version: 0.1

*/

#include "MCP4011.h"

// Constructor

MCP4011::MCP4011(uint8_t CS, uint8_t UD) {

  _CSPin = CS;
  _UDPin = UD;
  _debug = false;

}

MCP4011::MCP4011(uint8_t CS, uint8_t UD, bool DEBUG) {

  _CSPin = CS;
  _UDPin = UD;
  _debug = DEBUG;

}

// Methods

void MCP4011::setup() {

  pinMode(_UDPin, OUTPUT);
  pinMode(_CSPin, OUTPUT);

  digitalWrite(_CSPin, HIGH);   // _CSPin is active low, keep it HIGH at the beginning
  digitalWrite(_UDPin, HIGH);   // _UDPin -> U is active HIGH, keep it LOW at the beginning

}

void MCP4011::begin() {

  _tapPointer = DEFAULT_TAP_COUNT;

}

float MCP4011:: wiper() {

  return (_tapPointer) / TAP_NUMBER;

}

void MCP4011::inc() {    // return wiper count!


  if ((_tapPointer < TAP_NUMBER)) {

    // Note: The digitalWrite command is slow enough for the device. No additional delays are needed

    unsigned long _startIncTime = micros();
    digitalWrite(_UDPin, HIGH);   // We want the wiper to go UP

    //After at least 500ns bring _CSPin low
    digitalWrite(_CSPin, LOW);    // Start the command

    // /*  Increment command*/
    //*Subsequent rising edges of _UDPin move the wiper */
    // One tap
    digitalWrite(_UDPin, LOW);

    digitalWrite(_UDPin, HIGH);   // Last _UDPin state is HIGH
    // Here the wiper should have increased already

    // Leave the _CSPin pin ready for next instruction
    digitalWrite(_CSPin, HIGH);   // Release _CSPin to avoid changing the Pot

    _tapPointer++;

    if (_tapPointer >= TAP_NUMBER)
      _tapPointer = TAP_NUMBER;

    _incDelay = micros() - _startIncTime;

  }


}

void MCP4011::dec() {

  if ((_tapPointer > 0)) {

    unsigned long _startDecTime = micros();

    digitalWrite(_UDPin, LOW);   // We want the wiper to go DOWN

    //After at least 500ns bring _CSPin low
    digitalWrite(_CSPin, LOW); // Start the "move wiper" command

    // /*  Decrement command*/
    // One tap
    digitalWrite(_UDPin, HIGH);

    digitalWrite(_UDPin, LOW);
    // Here the wiper should have decreased already
    //*Subsequent falling edges of _UDPin move the wiper */

    // Leave the _CSPin pin ready for next instruction
    digitalWrite(_CSPin, HIGH);


    _tapPointer--;

    if (_tapPointer <= 0)
      _tapPointer = 0;

    _decDelay = micros() - _startDecTime;
  }


}

unsigned long MCP4011::incMicros() {

  return _incDelay;

}

unsigned long MCP4011::decMicros() {

  return _decDelay;

}

int MCP4011::taps() {

  return _tapPointer;   // value within [1-64] that points to the taps between resistors [0,63]
}

uint8_t MCP4011::setValue(float desiredR) {

  float _currentValue;
  float _distance;
  int _tapTarget;

  _tapTarget = round((desiredR * TAP_NUMBER) / (NOMINAL_RESISTANCE));
  _distance = abs(_tapPointer - _tapTarget);

  if (_debug){

  Serial.print("Distance to target: ");
  Serial.println(_distance);

  Serial.print("Target tap: ");
  Serial.println(_tapTarget);

  }

  if (_tapTarget < _tapPointer) {

    for (int i = _tapPointer; i > _tapTarget; i--) {

      dec();

    }

  } else if (_tapTarget > _tapPointer) {

    for (int i = _tapPointer; i < _tapTarget; i++) {

      inc();

    }

  } else {

    // Leave everything where it is

  }

  return _tapTarget;

}

void MCP4011::zeroWiper() {

  for (int i = DEFAULT_TAP_COUNT /*32*/; i >= 0; i--) {

    dec();

  }

  _tapPointer = 0;

}

void MCP4011::maxWiper() {

  for (int i = _tapPointer; i <= TAP_NUMBER; i++) {

    inc();

  }

  _tapPointer = TAP_NUMBER;

}

float MCP4011::readValue() {

  return (_tapPointer / TAP_NUMBER) * (NOMINAL_RESISTANCE);

}
