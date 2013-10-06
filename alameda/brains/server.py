
import web

import serial;

import time

import sendint;

render = web.template.render('/home/pi/PASA-2013-TIA-ELA/alameda/brains/html/')

urls = (
	'/', 'index',
	'/mode/all-one', 'ModeAllOn',
	'/mode/motion-detection', 'ModeMotionDetection',
	'/mode/wacko', 'ModeWaco',
	'/motion/detected', 'MotionDetected',
	'/motion/ended', 'MotionEnded'
)

MODE_ALL_ON = 1

MODE_MOTION_DETECTION = 2

mode = MODE_ALL_ON

ser = serial.Serial('/dev/ttyACM0', 9600);
#	time.sleep(2.0);
time.sleep(1.8);
ser.open();



class index:
    def GET(self):
        return render.modesForm()
		
class ModeAllOn:
    def GET(self):
	print "mode changed to all on"
	sendint.sendInt(ser, '1')
        return render.modesForm()

class ModeMotionDetection:
    def GET(self):
	print "mode changed to motion detection 1"
	sendint.sendInt(ser, '2')
        return render.modesForm()		

class ModeWaco:
    def GET(self):
	print "mode changed to wacko"
	sendint.sendInt(ser, '3')
        return render.modesForm()		
		
class MotionEnded:
    def GET(self):

	if mode == MODE_MOTION_DETECTION:
		print "mode changed to all on"
		sendint.sendInt(ser, '1')

        return render.modesForm()		

class MotionDetected:
    def GET(self):
	if mode == MODE_MOTION_DETECTION:
		print "motion detected"
		sendint.sendInt(ser, '2')

        return render.modesForm()
		

# start the web server
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()

