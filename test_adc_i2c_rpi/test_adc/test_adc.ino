//PROJET ISIS
//ATtiny85 and raspberryPi communication with I2C bus

#include "TinyWireS.h"                  // wrapper class for I2C slave routines
#define I2C_SLAVE_ADDR  0x27            // i2c slave address

void setup(){
 ADMUX =
           (1 << ADLAR) |     // left shift result
           (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
           (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
           (0 << MUX3)  |     // use ADC2 for input (PB4), MUX bit 3
           (0 << MUX2)  |     // use ADC2 for input (PB4), MUX bit 2
           (1 << MUX1)  |     // use ADC2 for input (PB4), MUX bit 1
           (0 << MUX0);       // use ADC2 for input (PB4), MUX bit 0
 ADCSRA = 
           (1 << ADEN)  |     // Enable ADC 
           (1 << ADPS2) |     // set prescaler to 64, bit 2 
           (1 << ADPS1) |     // set prescaler to 64, bit 1 
           (0 << ADPS0);      // set prescaler to 64, bit 0  

  TinyWireS.begin(I2C_SLAVE_ADDR);      // init I2C Slave mode
}

void loop()
{
  byte var = 0;
  ADCSRA |= (1 << ADSC);           // start ADC measurement
  var = ADCH;                      // get the sample value from ADCH 
  TinyWireS.send(var);           // send byte back to master
}
