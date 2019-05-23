/**************************************************************************/
/*!
    @file     Attiny_Core.ino
    @author   Tim301 & AlexandreBouton
    TinyWire:
      See TinyWire LICENSE, copyright 2017 by Rambo
      https://github.com/rambo/TinyWire/tree/rollback/TinyWireS
    EVERYTHING LEFT:
      License MIT,
    Software for Attiny85 to position motorized fader through i2c.
    @section  Audiovisual
    v1.0
    @comment  Workfull version but can be optimize.
*/
/**************************************************************************/

#include "TinyWireS.h"

#define I2C_SLAVE_ADDR  0x28        // i2c slave address
#define INT 1                       // Pin 1 wired to Raspberry pi to enable ATtiny
#define HBA 3                       // Pin 2 wired to Logical Input B of the H Bridge
#define HBB 4                       // Pin 3 wired to Logical Input A of the H Bridge
/* If the fader go to the wrong way, switch pin number of HBA & HBB.*/

#define ADC 0                       // Pin 1 used as ADC
/* Pin 1 is used by default as Reset. Attiny85's fuses must be set as following in AVRDUDE 
 * to disable it: -U lfuse:w:0x62:m -U hfuse:w:0x5f:m -U efuse:w:0xff:m 
 * Links: http://www.engbedded.com/fusecalc/ & https://github.com/zkemble/AVRDUDESS */
 
#define wait 1

uint16_t val = 0;                   // Fader value from the ADC 10bit
uint16_t target = 0;                // Target position  8bit send from i2c
const uint8_t delta = 2;            // Hysteresis
float start = 0;                    // Initialize counter


void setup() {
  pinMode(HBA, OUTPUT);             // Set pin 2 as output
  pinMode(HBB, OUTPUT);             // Set pin 3 as output
  pinMode(INT, INPUT);              // Set pin 6 as input
  go_to_zero();                     // Position fader to 0
  TinyWireS.begin(I2C_SLAVE_ADDR);  // Start ATtiny as i2c slave at defined adress
}

/**************************************************************************/

void position()
{ // Move the fader to the target position.

  val = analogRead(ADC);

  if (val > (target + delta)) {
    digitalWrite(HBA, LOW);           // Make the fader moving down
    digitalWrite(HBB, HIGH);
    delay(wait);                      // Do oscillations if we don't put outputs at low state.
    digitalWrite(HBA, LOW);           // Make the fader stop
    digitalWrite(HBB, LOW);
  }

  else if (val < (target - delta)) {
    digitalWrite(HBA, HIGH);          // Make the fader moving up
    digitalWrite(HBB, LOW);
    delay(wait);
    digitalWrite(HBA, LOW);           // Make the fader stop
    digitalWrite(HBB, LOW);
  }
}

/**************************************************************************/

void send_value()
{
  uint16_t read_val = analogRead(ADC);
  uint8_t tmp = read_val >>= 2;
  TinyWireS.send(tmp);
}

/**************************************************************************/

//Enable the motor for 200ms
void go_to_zero()
{
  digitalWrite(HBA, LOW);           // Make the fader moving down
  digitalWrite(HBB, HIGH);
  //Wait the fader is down
  delay(200);
  digitalWrite(HBA, LOW);           // Make the fader stop
  digitalWrite(HBB, LOW);
}

/**************************************************************************/

//Enable the motor for 200ms
void go_to_top()
{
  digitalWrite(HBA, HIGH);          // Make the fader moving up
  digitalWrite(HBB, LOW);
  delay(200);
  digitalWrite(HBA, LOW);           // Make the fader stop
  digitalWrite(HBB, LOW);
}

/**************************************************************************/

void loop() {
  if (digitalRead(1) == 0)
  {
    //The master (raspberry) send a value
    target = TinyWireS.receive();
    target <<= 2;
    //Take the current fader's position
    val = analogRead(ADC);
    if (target == 132) {                    // Send postion if get 33 from i2c
      send_value();
    }
    else {
      //If target and val are not equals
      //(i.e : if fader's position is not the wanted's position)
      if (target != 0 && target != 1020 && target != val) {
        start = millis();                                               // Start counter
        while ((val > (target + delta)) || (val < (target - delta)))    // While fader is not inside the hysteresis range
        {
          //For more precision the fader is mooved 50 time
          for (int i = 0; i < 50; i++)
          {
            val = analogRead(ADC);
            position();
          }
          if (millis() - start > 500) {                                // If time spended to positionning > 500 ms, quit the while
            break;
          }
        }
      }

      //else if the fader has to go down and is not down
      else if (target == 0 && val != 0)
      {
        go_to_zero();
      }

      //else if the fader has to go up and is not up
      //be careful to the value ! It's not 255 but 255>>=2
      else if (target == 1020 && val != 1020)
      {
        go_to_top();
      }
      send_value();
    }
  }
}
