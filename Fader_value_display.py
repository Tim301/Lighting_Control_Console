#PROJET ISIS
#This program reads a fader's value and displays it on a OLED screen
'''
GPIO on RPI :

MCP3008 
VDD -> +3.3V
VREF-> +3.3V
AGND -> GND
DGND -> GND
CLK -> Pi SCLK (23rd pin)
DOUT -> Pi MISO (21st pin)
DIN -> Pi MOSI (19th pin)
CS/SHDN -> Pi CE0 (24th pin)-

SSD1306
VCC -> +5V
GND -> seriously ?
SDA -> Pi SDA (3rd pin)
SCL -> Pi SCL (5th pin)

Farder PROFADER MF-914-B10K-10V
1 -> GND
2 -> ADC in
3 -> +5V
'''

import time
import Adafruit_GPIO.SPI as SPI
#ADC lib
import Adafruit_MCP3008
#OLED screen lib
import Adafruit_SSD1306
#Displaying libs
from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

		###Hardware SPI configuration###
		
SPI_PORT   = 0
SPI_DEVICE = 0
mcp = Adafruit_MCP3008.MCP3008(spi=SPI.SpiDev(SPI_PORT, SPI_DEVICE))
RST = 0

		###DISPLAY CONFIGURATION###
		
#Create display object 
disp = Adafruit_SSD1306.SSD1306_128_64(rst=RST)
#init display
disp.begin()
#Cleat display
disp.clear()
disp.display()
# Create blank image for drawing with mode '1' for 1-bit color.
width = disp.width
height = disp.height
image = Image.new('1', (width, height))
# Get drawing object to draw on image.
draw = ImageDraw.Draw(image)
#load default font
font = ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf', 20)


start=time.time()
raw_value = mcp.read_adc(0)
while True:
	new_raw_value = mcp.read_adc(0)

	#Because of a non stable input voltage, the read value is not constant
	#We need to do a hysteresis
	if new_raw_value < raw_value-5 or new_raw_value  > raw_value+5:
		raw_value = new_raw_value

	raw_value_str = str(raw_value)
	value = (raw_value*100)/1023 
	value_str = str(value)
	#print "The value is", value

	#Draw some text
	draw.text((0,0), value_str, font=font, fill=255)
        draw.text((40,0), "%", font=font, fill=255)
        draw.text((0,30), raw_value_str, font=font, fill=255)
	#Update display
	disp.image(image)
	disp.display()
	#Refresh text
	image = Image.new('1', (width, height))
	draw = ImageDraw.Draw(image)
	draw.text((0,0), " ", font=font, fill=255)
        draw.text((0,30), " ", font=font, fill=255)

#end
'''
draw.text((0,0), 'Canal : 512', font=font, fill=255)
font = ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf', 22)
draw.text((50,40), '50%', font=font, fill=255)
'''

