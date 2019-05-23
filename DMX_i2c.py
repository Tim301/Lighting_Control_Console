#!/usr/bin/env python

## Check if Serial0 is deleted in /boot/cmdline.txt
## TX Serial0 is on pin 8
## Use 2-5% of cpu (Pi2) while running

import serial
import struct
import smbus
import time
import RPi.GPIO as GPIO 

# Serial Setup for DMX transmission
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate = 250000,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None   
   )

# Remplacer 0 par 1 si nouveau Raspberry
bus = smbus.SMBus(1)
address1 = 0x28
address2 = 0x27
data1 = 33

#setup IO
GPIO.setmode(GPIO.BCM)     # set up BCM GPIO numbering
GPIO.setup(17, GPIO.OUT, initial = GPIO.HIGH)    # set GPIO17 as output (pin 11)   
GPIO.setup(27, GPIO.OUT, initial = GPIO.HIGH)    # set GPIO27 as output (pin 13)


# Initialize variable
universize = 512
dmxbuffer = [0] * universize

# Send Channels through DMX
def dmxfonction():
    global universize
    global dmxbuffer
    for i in range(0, universize, 1):
        ser.write(struct.pack('<H', dmxbuffer[i]))

# Test values
dmxbuffer[0] = 255     # Rouge
dmxbuffer[1] = 255     # Vert
dmxbuffer[2] = 255     # Blue
dmxbuffer[3] = 255     # Blanc
#dmxbuffer[4] = 25      # Master
dmxbuffer[5] = 0
# Main Loop
    
#Send datas to attiny
while 1:
        #for attiny 1
        start=time.time()
        GPIO.output(17, GPIO.LOW)
        bus.write_byte(address1, data1)
        dmxbuffer[4] = bus.read_byte(address1)
        GPIO.output(17, GPIO.HIGH)
        done=time.time()-start
        print(done)
        ser.send_break(duration=0.001)	# Break 1ms
        ser.write(struct.pack('<H', 0))	# Start Code
        dmxfonction()
        


