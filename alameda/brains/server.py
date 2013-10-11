
import web

import serial;

import time

import sendint;

render = web.template.render('/home/pi/PASA-2013-TIA-ELA/alameda/brains/html/')

urls = (
	'/', 'index',
	'/mode/all-one', 'ModeAllOn',
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
#	time.sleep(2.0);
time.sleep(1.8);
ser.open();



class index:
    def GET(self):
        return render.modesForm(mode)
		
class ModeAllOn:
    def GET(self):
	mode = MODE_ALL_ON
	sendint.sendInt(ser, '1')
	print "mode changed to all on"

        return render.modesForm(mode)

class ModeMotionDetection:
    def GET(self):

	mode = MODE_MOTION_DETECTION
	sendint.sendInt(ser, '2')
	print "mode changed to motion detection"

        return render.modesForm(mode)		

class ModeRandom:
    def GET(self):
	mode = MODE_RANDOM
	sendint.sendInt(ser, '3')
	print "mode changed to random"	

        return render.modesForm(mode)		
		
class MotionEnded:
    def GET(self):

	if mode == MODE_MOTION_DETECTION:
		print "motion ended"
		sendint.sendInt(ser, '1')

        return render.modesForm(mode)		

class MotionDetected:
    def GET(self):
	if mode == MODE_MOTION_DETECTION:
		print "motion detected"
		sendint.sendInt(ser, '2')

        return render.modesForm(mode)
		

# start the web server
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

