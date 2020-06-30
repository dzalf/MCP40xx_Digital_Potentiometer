/*
        MCP4011 Digital Potentiomenter from Microchip

        It consist of a volatile, 6-bit digital Pot. Contreoller by an UP/~DOWN serial interface
        63 taps, Power-on Recall

        ********** LIBRARY TEST *******************

        Model: MCP4011-503 --> 50k Ohms nominal
        Code: Set a voltage divider using the digital pot.
              Vary the resistance using a sinusoidal function
        Author: Daniel Melendrez

        Ver: 0.2 - General cleanup
        Date: March 2020
*/

#include <MCP4011.h>

#define QUANTA 4.94/1023      // Quantification factor (measured from +Vcc rail)
#define MS 0.001

// Pins declaration
const int UDPin = 2;   // Pin 2 is UP/DOWN
const int CSPin = 3;   // Pin 3 is CHIP SELECT

unsigned long previousDAQ;

int tapNum;
int analogIn;

byte pointer; 

float Rx = 0.0;
float resistorsArray[64];   // Array of floating-points to hold theoretical resistor values
float Res;
float voltsIn = 0.0;

const float step =  NOMINAL_RESISTANCE/64;
const float sampleRate =  100*MS;   // Fr [Hz]  
const float fs = 1*MS;    // Frequency of the sinewave multiplied by seconds conversion factor

MCP4011 pot(CSPin, UDPin);

void setup() {

  pot.setup();
  pot.begin();

  pot.maxWiper();

  Serial.begin(115200);

  Serial.println(F("*********************************"));
  Serial.println(F("  MCP4011 Digital Potentiometer  "));
  Serial.println(F("        LIBRARY ver 0.2          "));
  Serial.println(F("*********************************"));

  resistorsArray[0] = step;

  for(int i = 1; i < 64; i++){
      resistorsArray[i] = resistorsArray[i-1]  + step;
  }

  pinMode(A0, INPUT);

  previousDAQ = millis();

}

void loop() {

   unsigned long nowTime = millis();

  if(nowTime - previousDAQ >= 1/sampleRate){
       
    previousDAQ = nowTime;

    Rx = 10*sin(2 * PI * fs * nowTime);  // frequency of this sine wave must comply with Nyquist freq (Fr >= 2fs)

     pointer = map(Rx, -10,10, 0, 63);

      pot.setValue(resistorsArray[pointer]);

      analogIn = analogRead(A0);
  
      voltsIn = analogIn * QUANTA;

      //Serial.print("Volts: ");
      Serial.println(voltsIn, 2);   // Use Arduino's serial plotter to see this value
  
    
/*
      Serial.print("Rx: ");
      Serial.println(Rx, 3);

      Serial.print("Mapped Rx: ");
      Serial.println(pointer);

      Serial.print("From array: ");
      Serial.println(resistorsArray[pointer]);

     */
   }



}

