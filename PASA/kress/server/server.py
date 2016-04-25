
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
	'/mode/blink', 'ModeBlink',
	'/mode/chaser', 'ModeChaser',
)

MODE_ALL_ON = 1

MODE_BLINK = 2	

MODE_CHASER = 3	

mode = MODE_ALL_ON

ser = None

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


class ModeBlink:
    def GET(self):

	global mode

	mode = MODE_BLINK

	sendInt('2')
	print "mode changed to BLINK"	

        return render.modesForm(mode)


class ModeChaser:
    def GET(self):

	global mode

	mode = MODE_CHASER

	sendInt('3')
	print "mode changed to CHASER\n"	

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
