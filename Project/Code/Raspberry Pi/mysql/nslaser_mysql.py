import MySQLdb
import sys
import os
import subprocess
import time

CLEAR_DB = 'c'
WRITE_TO_DB = 'w'
VERIFY = 'v'
DISP_DB = 'd'


def clear_database() :
	cur.execute("DELETE FROM targets")
	return;

def write_target_to_database(target_name) : 
	os.system("python serial/serialAll.py r 0") #update the distance value

	cur.execute("SELECT * FROM system_info")

	for row in cur.fetchall() :
		p = row[0]
		t = row[1]
		d = row[2]

	#need to check values

	while (p > 180 or p < 0) :
		os.system("python serial/serialAll.py p 0") #get current pan position

		cur.execute("SELECT * FROM system_info")

		for row in cur.fetchall() :
			p = row[0]

	while (t > 180 or t < 0) :
		os.system("python serial/serialAll.py t 0") #get current tilt position

		cur.execute("SELECT * FROM system_info")

		for row in cur.fetchall() :
			p = row[0]


	print "Successfully wrote " + str(target_name) + " to database."

	cur.execute("INSERT INTO targets (name, pan, tilt, distance) VALUES('" + str(target_name) + "', " + str(p) + ", " + str(t) + ", " + str(d) + ")")
	return;

def verify_targets() :
	cur.execute("SELECT * FROM targets")

	ret_string = ""

	count = 0

	for row in cur.fetchall() :
		name = row[0]
		pan = row[1]
		tilt = row[2]
		distance = float(row[3])

		os.system("python serial/serialAll.py p " + str(pan));
		os.system("python serial/serialAll.py t " + str(tilt));
		time.sleep(1)
		curDistance = float(subprocess.check_output("python serial/serialAll.py r 2", shell=True))

		if abs(curDistance - distance) > .5 : 
			if count >= 1 :
				ret_string = ret_string + ", "

			ret_string = ret_string + str(name) + " was measured to be " + str(curDistance) + " m as apposed to targeted at " + str(distance) + " m"

			count = count + 1


	if count == 0 :
		print "All targets are verified."
	else :
		print "Targets are off: " + ret_string + "."

	return

def display_db() :
	cur.execute("SELECT * FROM targets")

	count = 0

	ret_string = "\n\nTarget\t\tPan\tTilt\tDist (m)"

	for row in cur.fetchall() :
		name = row[0]
		pan = row[1]
		tilt = row[2]
		distance = float(row[3])

		ret_string = ret_string + "\n" + str(name) 

		if len(str(name)) >= 12 :
			ret_string = ret_string + "\t"
		elif len(str(name)) >= 6 :
			ret_string = ret_string + "\t\t"
		else :
			ret_string = ret_string + "\t\t\t"

		ret_string = ret_string + str(pan) + "\t" + str(tilt) + "\t" + str(distance)

		count = count + 1

	if count > 0 :
		print ret_string
	else :
		print "No targets in database."

command = str(sys.argv[1])

if (command == CLEAR_DB) :
	clear_database()
elif (command == WRITE_TO_DB) :
	write_target_to_database(sys.argv[2])
elif (command == VERIFY) :
	verify_targets()
elif (command == DISP_DB) :
	display_db()

db.commit()
cur.close()
db.close()