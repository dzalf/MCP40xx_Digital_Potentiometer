# MCP4011_Digital_Potentiometer

Arduino/Teensy (C/C++) library for Microchip MCP4011 64 taps digital [potentiometer](http://ww1.microchip.com/downloads/en/DeviceDoc/20001978D.pdf)

Library usage:

1. Instantiate a new object as:

      MCP4011 digipot(CS Pin, UD Pin)
      
    1.1 An overloaded constructor is available. It makes possible to debug the code via a third element:
      
      MCP4011 digipot(CS Pin, UD Pin, true/false) 
      
2. Setup and begin the digital pot:
    
    digipot.setup() --> assigns and initialises the digital pins
    digipot.begin() --> sets the initial position of the wiper 
                        #TODO: set three possible states: minimum wiper, 50% wiper or max wiper
    
3. Increase/decrease the pot's value using the inc()/dec() methods

Please read both .h and .cpp files are they are self-explanatory.

If you have any suggestions/commits please feel free.

Let's work together :smiley:

Happy tinkering :beer:

dzalf
