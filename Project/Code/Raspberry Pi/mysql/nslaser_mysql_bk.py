import MySQLdb
import sys
import os
import subprocess
import time

CLEAR_DB = 'c'
WRITE_TO_DB = 'w'
VERIFY = 'v'

db = MySQLdb.connect(host="localhost", user="root", passwd="system", db="nslaser_db")
cur = db.cursor()

def clear_database() :
	cur.execute("DELETE FROM targets")
	return;

def write_target_to_database(target_name) : 
	os.system("python serial/serialAll.py r 1") #update the distance value

	cur.execute("SELECT * FROM system_info")

	for row in cur.fetchall() :
		p = row[0]
		t = row[1]
		d = row[2]

	print "writing to db"

	cur.execute("INSERT INTO targets (name, pan, tilt, distance) VALUES('" + str(target_name) + "', " + str(p) + ", " + str(t) + ", " + str(d) + ")")
	return;

def verify_targets() :
	cur.execute("SELECT * FROM targets")

	ret_string = ""

	for row in cur.fetchall() :
		name = row[0]
		pan = row[1]
		tilt = row[2]
		distance = float(row[3])

		os.system("python serial/serialAll.py p " + str(pan));
		os.system("python serial/serialAll.py t " + str(tilt));
		time.sleep(1)
		curDistance = float(subprocess.check_output("python serial/serialAll.py r 0", shell=True))

		if abs(curDistance - distance) > .5 : 
			ret_string = ret_string + str(name) + " was measured to be " + str(curDistance) + " m as apposed to targeted at " + str(distance) + " m, "


	print "Targets are off: " + ret_string

	return

command = str(sys.argv[1])

if (command == CLEAR_DB) :
	clear_database()
elif (command == WRITE_TO_DB) :
	write_target_to_database(sys.argv[2])
elif (command == VERIFY) :
	verify_targets()

db.commit()
cur.close()
db.close()