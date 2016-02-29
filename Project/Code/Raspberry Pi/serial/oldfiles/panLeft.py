import serial
import time

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE, BAUD)

time.sleep(3)

ser.write('p100')
ser.flush()

