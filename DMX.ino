#include <ArduinoRS485.h>
#include <ArduinoDMX.h>
#include <math.h>

const int universeSize = 10;
int brightness_M=255;
int brightness_null=0;
int brightness_R=255, brightness_G=0, brightness_B=0;

void setup() {
  //On démarre la communication série avec la fréquence 9600
  Serial.begin(9600);

  //On démarre la communication DMX
  DMX.begin(universeSize); 
  
  pinMode(A1,INPUT);
  
}

void loop() {
  //On démarre la transmission des trames DMX
  DMX.beginTransmission();
    
  DMX.write(1, brightness_M); //Cannal 1 : MASTER, on doit donc lui définir une valeur de brightness avant les autres couleur
  DMX.write(2, brightness_R);
  DMX.write(3, brightness_G);
  DMX.write(4, brightness_B);
  
  DMX.endTransmission();

  //DMX_Strobe_RGBW(brightness_M ,brightness_R, brightness_G, brightness_B, 100);
  //DMX_Strobe(brightness_R,30);

  byte fader = (analogRead(A1))/4;
      
  //DMX_Strobe_RGBW(brightness_M, brightness_R, brightness_G, brightness_B, static_cast<int>(fader*2)); 
  Fade(brightness_M, 5, 30); 
}

//Fonction strobe avec uniquement le master
void DMX_Strobe(int &brightness,const int &delais)
{
  if(brightness==255)
    brightness = brightness_null;
  else if (brightness==0)
    brightness=255;

  //Condition pour les erreurs de lecture du fader
  if (delais >= 227*2)
    brightness_M = 0;
  else if (delais <= 5*2)
    brightness_M = 255;
  
  delay(delais);
}

//Fonction strobe qui fait varier succéssivement les couleurs
void DMX_Strobe_RGBW(int &brightness_M, int &brightness_R, int &brightness_G, int &brightness_B, const int &delais)
{
  if(brightness_M != 255)
    brightness_M = 255;
  
  if (brightness_R == 255 && brightness_G == 255 && brightness_B == 255)
  {
    brightness_R=0;
    brightness_G=255;
    brightness_B=0;
  }
  else if (brightness_G == 255)
  {
    brightness_G=0;
    brightness_B=255;
    brightness_R=0;
  }
  else if(brightness_B == 255)
  {
    brightness_B=0;
    brightness_R=255;
    brightness_G=0;
  }
  else if ( brightness_R == 255)
  {
    brightness_R=255;
    brightness_G=255;
    brightness_B=255;
  } 

  //Condition pour les erreurs de lecture du fader
  if (delais >= 227*2)
    brightness_M = 0;
  else if (delais <= 5*2)
    brightness_R = brightness_G = brightness_B = 255;

  delay(delais);
}

void Fade(int &brightness, int fadeAmount, const int &delais)
{
   // change the brightness for the next round
  brightness += fadeAmount;

  // reverse fade direction when on edge of range
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }

  // delay for dimming effect
  delay(delais);
}
