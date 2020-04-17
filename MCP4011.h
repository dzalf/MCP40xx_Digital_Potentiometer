
/*
    Microchip 64 taps Single Digital Potentiometer
    Simple two-wire UP/DOWN interface
    Author: Daniel Melendrez
    Date: March 2020 (COVID-19 Vibes)
    Version: 0.1

*/

#ifndef MCP4011_h
#define MCP4011_h

#include "Arduino.h"

#define TAP_NUMBER 63.0             // Total taps, 63 resistors. Wiper values are from 0x00 to 0x3F
#define DEFAULT_TAP_COUNT 31     // Half way resistance
#define NOMINAL_RESISTANCE 49764    // 50000 theoretical --> Real value measured using maxPot method
#define WIPER_RESISTANCE 39.5   // 75 typical (According to datasheet)

class MCP4011 {

  public:

    const float nominal = NOMINAL_RESISTANCE;
    // Constructors:
    MCP4011(uint8_t cs, uint8_t ud);
    MCP4011(uint8_t cs, uint8_t ud, bool dbg);

    // Methods:
    void setup(void);
    void begin(void);
    int taps(void);
    float wiper(void);
    void inc(void);
    void dec(void);
    void zeroWiper(void);
    void maxWiper(void);
    float readValue(void);
    uint8_t setValue(float);
    unsigned long incMicros(void);
    unsigned long decMicros(void);

  private:

    uint8_t _tapPointer;
    uint8_t _CSPin;
    uint8_t _UDPin;
    unsigned long _incDelay;
    unsigned long _decDelay;
    bool _debug;

};

#endif
