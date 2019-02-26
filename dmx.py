#!/usr/bin/env python
                
import time
import serial
                
ser = serial.Serial(
	port='/dev/ttyAMA0',
   baudrate = 250000,
   parity=serial.PARITY_NONE,
   stopbits=serial.STOPBITS_ONE,
   bytesize=serial.EIGHTBITS,
   timeout=None   
   )
           
universize = 512

def dmxfonction():
	global dmxbuffer
	for i in range(0, 511):
		ser.write(dmxbuffer[i])

dmxbuffer = [0] * 512
dmxbuffer[0] = 126		# Master
dmxbuffer[1] = 255		# Red
dmxbuffer[2] = 0			# Green
dmxbuffer[3] = 255 		# Blue
      
while 1:
	send_break(duration=0.001)
	ser.write(0)
	dmxfonction()           
