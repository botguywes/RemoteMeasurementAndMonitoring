import serial
import time

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE, BAUD)

#delay to get the serial port set up
time.sleep(2)

ser.flushInput()
ser.write('r')
time.sleep(1)
result = ser.readline()
print float(result)