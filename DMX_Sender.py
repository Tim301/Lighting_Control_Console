#!/usr/bin/env python

## Check if Serial0 is deleted in /boot/cmdline.txt
## TX Serial0 is on pin 8
## Use 2-5% of cpu (Pi2) while running

import time
import serial
import struct

# Serial Setup for DMX transmission
ser = serial.Serial(
    port='/dev/ttyAMA0',
    baudrate = 250000,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None   
   )

# Initialize variable
universize = 512
dmxbuffer = [0] * universize
master = 255

# Send Channels through DMX
def dmxfonction():
    global universize
    global dmxbuffer
    global master
    for i in range(0, universize, 1):
        ser.write(struct.pack('<H', (dmxbuffer[i]/255*master))

# Test values
dmxbuffer[0] = 126      # Master
dmxbuffer[1] = 255      # Red
dmxbuffer[2] = 128       # Green
dmxbuffer[3] = 0      # Blue

# Main Loop
while 1:
    ser.send_break(duration=0.001)	# Break 1ms
    ser.write(struct.pack('<H', 0))	# Start Code
    dmxfonction()           		
