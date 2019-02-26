#!/usr/bin/env python
                
import time
import serial
import struct

# Serial Setup for DMX
ser = serial.Serial(
    port='/dev/ttyAMA0',
    baudrate = 250000,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None   
   )
           
universize = 512

# Send Channel through DMX
def dmxfonction():
    global universize
    global dmxbuffer
    for i in range(0, universize, 1):
        ser.write(struct.pack('<H', dmxbuffer[i]))

dmxbuffer = [0] * 512
dmxbuffer[0] = 126      # Master
dmxbuffer[1] = 255      # Red
dmxbuffer[2] = 128        # Green
dmxbuffer[3] = 0      # Blue
      
while 1:
    ser.send_break(duration=0.001)	# Break 1ms
    ser.write(struct.pack('<H', 0))	# Start Code
    dmxfonction()           		
