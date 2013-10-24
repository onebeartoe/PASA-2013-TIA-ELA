
import web

import serial;

import time

import sendint;

render = web.template.render('/cygdrive/c/home/owner/github/PASA-2013-TIA-ELA-master/kress/server/html/')

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

	sendint.sendInt(ser, '1')
	print "mode changed to all on"

        return render.modesForm(mode)


class ModeRandom:
    def GET(self):

	global mode

	mode = MODE_RANDOM

	sendint.sendInt(ser, '2')
	print "mode changed to random"	

        return render.modesForm(mode)


class ModeLadder:
    def GET(self):

	global mode

	mode = MODE_LADDER

	sendint.sendInt(ser, '3')
	print "mode changed to ladder\n"	

        return render.modesForm(mode)
		
# start the web server
if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
