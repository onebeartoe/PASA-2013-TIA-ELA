
import web

import serial;

import time

#import sendint;

import serial;
import serial.serialutil;
import time;

render = web.template.render('/home/pi/PASA-2013-TIA-ELA/kress/server/html/')

urls = (
	'/', 'index',
	'/mode/all-on', 'ModeAllOn',
	'/mode/random', 'ModeRandom',
	'/mode/ladder', 'ModeLadder',
)

MODE_ALL_ON = 1

MODE_RANDOM = 2	

MODE_LADDER = 3	

mode = MODE_ALL_ON

ser = None
#ser = serial.Serial('/dev/ttyACM0', 9600);
#time.sleep(2.0);
#ser.open();

class index:
    def GET(self):
        return render.modesForm(mode)
		
class ModeAllOn:
    def GET(self):

	global mode

	mode = MODE_ALL_ON

	sendInt('1')
	print "mode changed to all on"

        return render.modesForm(mode)


class ModeRandom:
    def GET(self):

	global mode

	mode = MODE_RANDOM

	sendInt('2')
	print "mode changed to random"	

        return render.modesForm(mode)


class ModeLadder:
    def GET(self):

	global mode

	mode = MODE_LADDER

	sendInt('3')
	print "mode changed to ladder\n"	

        return render.modesForm(mode)



def sendInt(i):

	global ser
	
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

		
# start the web server
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
