/**************************************************************************/
/*!
    @file     DMX_ESP32.ino
    @author   Tim301
    LXESP32DMX:
      License BSD, see LXESP32DMX LICENSE, copyright 2017 by Claude Heintz
    EVERYTHING LEFT:
      License MIT,
    Simple Lighting Console with 12 channels using ESP32 DMX Driver
    @section  HISTORY
    v1.01
*/
/**************************************************************************/

#include <LXESP32DMX.h>
#include "esp_task_wdt.h"

#define DMX_SERIAL_OUTPUT_PIN 17            //Define TX pin

#define CH1 36                              //Define Channel_1 pin
#define CH2 39
#define CH3 34
#define CH4 35
#define CH5 32
#define CH6 33
#define CH7 25
#define CH8 26
#define CH9 27
#define CH10 14
#define CH11 12
#define CH12 13
#define MASTER 15

uint8_t dmxbuffer[DMX_MAX_FRAME];           //Array to store DMX values

/************************************************************************/

void setup() {
  
  Serial.begin(115200);
  Serial.println("setup");
   
  pinMode(DMX_SERIAL_OUTPUT_PIN, OUTPUT);
  ESP32DMX.startOutput(DMX_SERIAL_OUTPUT_PIN);
  setupADC();                               //Lunch ADC setup
  
  Serial.println("setup complete");
}

/************************************************************************/

  /*  ADC Config parameters  */
void setupADC() {
  analogSetWidth(12);                       //Sets the sample bits and read resolution.
  analogSetCycles(8);                       //Set number of cycles per sample.
  analogSetSamples(1);                      //Set number of samples in the range.
  analogSetClockDiv(1);                     //Set the divider for the ADC clock.
  analogSetAttenuation(ADC_11db);           //Set the attenuation for all channels.
  analogSetPinAttenuation(CH1, ADC_11db);   //Set the attenuation for particular pin.
  adcAttachPin(CH1);                        //Attach pin to ADC.
  adcStart(CH1);                            //Start ADC conversion on attached pin's bus.
  analogSetPinAttenuation(CH2, ADC_11db);
  adcAttachPin(CH2);
  adcStart(CH2);
  analogSetPinAttenuation(CH3, ADC_11db);
  adcAttachPin(CH3);
  adcStart(CH3);
  analogSetPinAttenuation(CH4, ADC_11db);
  adcAttachPin(CH4);
  adcStart(CH4);
  analogSetPinAttenuation(CH5, ADC_11db);
  adcAttachPin(CH5);
  adcStart(CH5);
  analogSetPinAttenuation(CH6, ADC_11db);
  adcAttachPin(CH6);
  adcStart(CH6);
  analogSetPinAttenuation(CH7, ADC_11db);
  adcAttachPin(CH7);
  adcStart(CH7);
  analogSetPinAttenuation(CH8, ADC_11db);
  adcAttachPin(CH8);
  adcStart(CH8);
  analogSetPinAttenuation(CH9, ADC_11db);
  adcAttachPin(CH9);
  adcStart(CH9);
  analogSetPinAttenuation(CH10, ADC_11db);
  adcAttachPin(CH10);
  adcStart(CH10);
  analogSetPinAttenuation(CH11, ADC_11db);
  adcAttachPin(CH11);
  adcStart(CH11);
  analogSetPinAttenuation(CH12, ADC_11db);
  adcAttachPin(CH12);
  adcStart(CH12);
  analogSetPinAttenuation(MASTER, ADC_11db);
  adcAttachPin(MASTER);
  adcStart(MASTER);  
}

/*   ADC fonction  */
uint8_t ADC(uint8_t x){                     
    uint8_t preset = (analogRead(x)) >> 4;        //Get value from CHx
    uint8_t master = (analogRead(MASTER)) >> 4;   //Get value from MASTER
    uint8_t result = (unsigned int) (preset*master/255);  //Multiply Channel level by Master factor
  return result;
}

/*  DMX Generator fonction  */
void copyDMXToOutput(void) {
  xSemaphoreTake( ESP32DMX.lxDataLock, portMAX_DELAY );
  for (int i=1; i<DMX_MAX_FRAME; i++) {
      ESP32DMX.setSlot(i , dmxbuffer[i]);
   }
   xSemaphoreGive( ESP32DMX.lxDataLock );
}

/************************************************************************/

void loop() {
  
  /*  Save Channels State   */
  dmxbuffer[1] = ADC(CH1);
  dmxbuffer[2] = ADC(CH2);
  dmxbuffer[3] = ADC(CH3);
  dmxbuffer[4] = ADC(CH4);
  dmxbuffer[5] = ADC(CH5);
  dmxbuffer[6] = ADC(CH6);
  dmxbuffer[7] = ADC(CH7);
  dmxbuffer[8] = ADC(CH8);
  dmxbuffer[9] = ADC(CH9);
  dmxbuffer[10] = ADC(CH10);
  dmxbuffer[11] = ADC(CH11);
  dmxbuffer[12] = ADC(CH12);

  //Serial.println((analogRead(MASTER))/16);
  copyDMXToOutput();                            //Send channels values to DMX Generator Fonction
  esp_task_wdt_feed();
  
}
