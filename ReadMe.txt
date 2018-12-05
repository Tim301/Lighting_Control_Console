# Lighting_Control_Console
An open source lighting control console developed by MASTER's degree students of DREAM course at Valenciennes.
-> https://formations.uphf.fr/cdm/subProgram/FR_RNE_0593279U_PR_SOF-15676/FR_RNE_0593279U_PR_SOF-15679

DMX_Core.ino use Arduino Uno to create DMX512 signals for RS485 chip. // Actually in progress.
  Equipements:
   - Arduino Uno
   - Grove Dmx512 or similar
   - Cables
  How to use:
  Connect DMX chip input pin to Arduino's TX pin.
  
Attiny_Fader.ino use a Attiny85 to send and receive fader position with I2C.
  Equipements:
   - Attiny 85
   - L9110H H Bridge (DIP)
   - Motorized fader like SL9/01V96     // We use a PRO-Fader MF-914PFL-B10K-10V
 See Pinout:    // Not available yet
