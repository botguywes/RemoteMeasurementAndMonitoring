import serial
import time

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE, BAUD)

#delay to get the serial port set up
time.sleep(2)

ser.write('t80')
ser.flush()
time.sleep(1)