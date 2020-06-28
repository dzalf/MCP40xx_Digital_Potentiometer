# MCP40xx_Digital_Potentiometer

Arduino/Teensy (C/C++) library for Microchip MCP4011/12/13/14 64 taps digital [potentiometer](http://ww1.microchip.com/downloads/en/DeviceDoc/20001978D.pdf)

Library usage:

1. Instantiate a new object as:

      MCP40xx digipot(CS Pin, UD Pin)
      
    1.1 An overloaded constructor is available. It makes possible to debug the code via a third element:
      
      MCP40xx digipot(CS Pin, UD Pin, true/false) 
      
2. Setup and begin the digital pot:
    
    digipot.setup() --> assigns and initialises the digital pins
    digipot.begin() --> sets the initial position of the wiper 
                        #TODO: set three possible states: minimum wiper, 50% wiper or max wiper
    
3. Increase/decrease the pot's value using the inc()/dec() methods.

4. Methods for retrieving the approximate resistance value, tap position and increment/decrement times (in microseconds) are included.

Please read both .h and .cpp files as they are self-explanatory.

If you have any suggestions/pull requests please feel free to join me on the development.

Let's work together :smiley:

Happy tinkering :beer:

dzalf
