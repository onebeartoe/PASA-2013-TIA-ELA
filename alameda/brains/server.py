
import web

import serial;

import time

import sendint;

render = web.template.render('/home/pi/PASA-2013-TIA-ELA/alameda/brains/html/')

urls = (
	'/', 'index',
	'/mode/all-on', 'ModeAllOn',
	'/mode/motion-detection', 'ModeMotionDetection',
	'/mode/random', 'ModeRandom',
	'/motion/detected', 'MotionDetected',
	'/motion/ended', 'MotionEnded'
)

MODE_ALL_ON = 1

MODE_MOTION_DETECTION = 2

MODE_RANDOM = 3	

mode = MODE_ALL_ON

ser = serial.Serial('/dev/ttyACM0', 9600);
time.sleep(2.0);
ser.open();

class index:
    def GET(self):
        return render.modesForm(mode)
		
class ModeAllOn:
    def GET(self):

	global mode

	mode = MODE_ALL_ON

	sendint.sendInt(ser, '1')
	print "mode changed to all on"

        return render.modesForm(mode)

class ModeMotionDetection:
    def GET(self):

	global mode

	mode = MODE_MOTION_DETECTION

	sendint.sendInt(ser, '2')
	print "mode changed to motion detection"

        return render.modesForm(mode)		

class ModeRandom:
    def GET(self):

	global mode

	mode = MODE_RANDOM

	sendint.sendInt(ser, '3')
	print "mode changed to random"	

        return render.modesForm(mode)		
		
class MotionEnded:
    def GET(self):
	
	global mode

	if mode == MODE_MOTION_DETECTION:
		mode = MODE_ALL_ON
		print "motion ended"
		sendint.sendInt(ser, '1')

        return "motion ended"

class MotionDetected:
    def GET(self):

	global mode

	if mode == MODE_MOTION_DETECTION:
		print "motion detected"
		sendint.sendInt(ser, '2')

        return "motion detected"
		

# start the web server
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

