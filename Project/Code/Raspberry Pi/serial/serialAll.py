import sys
import serial
import time
import MySQLdb

DEVICE = '/dev/ttyACM0'
BAUD = 9600
ser = serial.Serial(DEVICE, BAUD)

#delay to get the serial port set up
#time.sleep(1)

db = MySQLdb.connect(host="localhost", user="root", passwd="system", db="nslaser_db")
cur = db.cursor()

PAN_SERVO = 'p'
TILT_SERVO = 't'
LRF_READ = 'r'

def moveServo(servo, position) :
  ser.write(servo + str(position))
  ser.flush()
  time.sleep(1)

  p = int(ser.readline())
  
  if servo == 'p' :
    cur.execute("UPDATE system_info SET pan = " + str(p))

  if servo == 't' : 
    cur.execute("UPDATE system_info SET tilt = " + str(p))

  return

def readLaser(printM) :
  ser.write(LRF_READ)
  ser.flush()
  time.sleep(1)
  result = float(ser.readline())

  if (int(printM) == 1) :
    print str(result) + " m"      #print so that the ajax call can pick it up
  elif (int(printM) == 2) :
    print str(result)


  cur.execute("UPDATE system_info SET distance = " + str(float(result)))

  return float(result)

command = str(sys.argv[1])

if(command == LRF_READ) :
  readLaser(sys.argv[2])
elif(command == TILT_SERVO or command == PAN_SERVO) :
  pos = str(sys.argv[2])
  moveServo(command, pos)

ser.close()

db.commit()
cur.close()
db.close()