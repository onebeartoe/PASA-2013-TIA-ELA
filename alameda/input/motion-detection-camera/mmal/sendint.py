import serial;

def sendInt(i):
	ser = serial.Serial('/dev/ttyACM0', 9600);

	import time
#	time.sleep(2.0);
	time.sleep(1.8);

	ser.open();

	ser.write(i);

	ser.close();

