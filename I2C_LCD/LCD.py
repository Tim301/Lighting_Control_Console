#This is a test of the lcddriver.py and i2c_lib.py 
#This code make a little LCD screen (16*2) display a text and twinkle
#To make the screen communicate with the RPI, plug the 3 and 5 pins (GPIO 2 and 3)
#Pin 3 -> I2C SDA
#Pin 5 -> I2C SDL

import lcddriver
from time import*

lcd=lcddriver.lcd()
lcd.lcd_clear()

x=input("Combien de clignotations ?")
y=0

#Ne pas utiliser input. Pour les chaines de caractere, utiliser raw_input
str1 = raw_input("Qu'ecrire sur la premiere ligne ?")
str2 = raw_input("Qu'ecrire sur la deuxieme ligne ?")

while y < x:
	lcd.lcd_display_string(str1, 1)
	lcd.lcd_display_string(str2, 2)
	sleep(1)
	lcd.lcd_clear()
	sleep(0.5)
	y += 1
