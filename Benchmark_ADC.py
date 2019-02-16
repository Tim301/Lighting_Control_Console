# Benchmark_ADC v1.1
# Author: Tim301

import time
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008


# Software SPI configuration:
CLK  = 18
MISO = 23
MOSI = 24
CS   = 25
mcp = Adafruit_MCP3008.MCP3008(clk=CLK, cs=CS, miso=MISO, mosi=MOSI) 

# Settings
print("Simple Benchmark for ADC MCP3008")
nb = int(input('Numbre of sample: '))

# Benchmarking on ADC channel 0
print("Start Benchmarking on ADC channel 0")
start=time.time()
i = 1
while i <= nb:  
	mcp.read_adc(0)
	i=i+1
done=time.time()-start

# Result
print("Done")
if nb ==1:
	print("For " +  str(nb) + " sample, it need " + str(done) + "s.")
else:
	print("For " +  str(nb) + " samples, it need " + str(done) + "s.")
