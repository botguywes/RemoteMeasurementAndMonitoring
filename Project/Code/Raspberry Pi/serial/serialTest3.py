import serial
import time

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE, BAUD)

#delay to get the serial port set up
time.sleep(3)

PAN_SERVO = 'p'
TILT_SERVO = 't'
LRF_READ = 'r'

tilt_servo_pos = 90
pan_servo_pos = 90

def moveServo(servo, position) :
  ser.write(servo + str(position))
  ser.flush()
  time.sleep(1)
  return

def pTest() :
  moveServo(PAN_SERVO, 100)

  moveServo(PAN_SERVO, 80)

  moveServo(PAN_SERVO, 100)

  moveServo(PAN_SERVO, 80)
  return

def laserTest() :
  ser.flushInput()
  ser.write(LRF_READ)
  time.sleep(1)
  result = ser.readline()
  print float(result)
  return float(result)

pTest()

laserTest()
