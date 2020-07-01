
/*
    Microchip 63 taps Single Digital Potentiometer
    Simple two-wire UP/DOWN interface
    Author: dzalf - Daniel Melendrez
    Date: June 2020 (COVID-19 Vibes)
    Version: 1.1.1  - Initial deployment
             1.1.2  - General cleanup. Implemented new and overloaded methods that allow
                    to select the desired tap. It is now possible to select the nominal 
                    resistance value or override it by setting the measured value

*/

#ifndef MCP40xx_h
#define MCP40xx_h

#include "Arduino.h"

#define MCP40xx_TAP_NUMBER 63.0               // Total taps, 63 resistors. Wiper values are from 0x00 to 0x3F
#define MCP40xx_DEFAULT_TAP_COUNT 31          // Half way resistance
#define MCP40xx_NOMINAL_RESISTANCE 50000      // 50000 theoretical --> Real value measured using maxPot method
#define MCP40xx_WIPER_RESISTANCE 75           // 75 typical (According to datasheet)

class MCP40xx {

  public:

    // Constructors:
    MCP40xx(uint8_t cs, uint8_t ud);
    MCP40xx(uint8_t cs, uint8_t ud, bool dbg);
    
    // Members
    
    //The model of the device sets the value of the full-scale resisatance
	enum Model {
		MCP4011,
		MCP4012,
		MCP4013,
        MCP4014
	};
    
    const char MCP4011_LBL[8] PROGMEM = "MCP4011";
    const char MCP4012_LBL[8] PROGMEM = "MCP4012";
    const char MCP4013_LBL[8] PROGMEM = "MCP4013";
    const char MCP4014_LBL[8] PROGMEM = "MCP4014";
    
    const char *const DIGIPOT_LABELS[4] PROGMEM = {MCP4011_LBL, MCP4012_LBL, MCP4013_LBL, MCP4014_LBL};
	
    // Methods:

    // Setup the device's connections
    void setup(void);
    // Begin the digital potentiometer using a nominal resistance of 100 kOhms
    void begin(void);
    // Begin the digital potentiometer with a custom value. Overloaded method.
    void begin(float);
    // Retrieve the currently set tap
    int taps(void);
    // Retrieve the fractional position of the wiper
    float wiper(void);
    // Issue a single tap increment command
    void inc(void);
    // Issue a single tap decrement command
    void dec(void);
    // Set the wiper position to the minimum
    void zeroWiper(void);
    // Set the wiper position to the maximum
    void maxWiper(void);
    // Retrieve a mathematical approximation of the current resistance value
    float readValue(void);
    // Set the closest possible resistance value -> mathematical approximation
    uint8_t setValue(float);
    // Set the tap to a desired position within its nominal range
    uint8_t setTap(uint8_t);
    // Read the time it took for increasing the tap
    unsigned long incMicros(void);
    // Read the time it took for decreasing the tap
    unsigned long decMicros(void);
    // Read the time it took for setting the tap
    unsigned long setMicros(void);

  private:

    uint8_t _tapPointer;
    float _nominalResistance;

  protected:

    uint8_t _CSPin;
    uint8_t _UDPin;
    unsigned long _incDelay;
    unsigned long _decDelay;
    unsigned long _setDelay;
    bool _debug;

};

#endif
