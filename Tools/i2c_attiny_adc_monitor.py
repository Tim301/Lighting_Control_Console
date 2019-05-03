import smbus
import time

# Remplacer 0 par 1 si nouveau Raspberry
bus = smbus.SMBus(1)
address = 0x27


while 1:
	#reponse = bus.read_byte(address)
	#reponse2 = bus.read_byte(address)
	#if reponse != reponse2 :
	#	print "Reponse de l'Attiny", reponse2
	#else :
	#	print "Pas de reponse"
	#	time.sleep(0.01)

	reponse = bus.read_byte(address)
	print reponse
	time.sleep(0.01)

