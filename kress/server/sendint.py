import serial;
import serial.serialutil;

def sendInt(ser, i):
	
	if ser is None:
	
		print "serial is null, trying to initialize"
	
		try:
			ser = serial.Serial('/dev/ttyACM0', 9600);
			time.sleep(2.0);
			ser.open();			
		except (OSError, serial.serialutil.SerialException):
			print "could not open the serial port"
	
	if ser is not None:
		print "writing int to serial"
		ser.write(i);
