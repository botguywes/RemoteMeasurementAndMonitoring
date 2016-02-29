import serial
import time

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE, BAUD)

ser.write('p100')
