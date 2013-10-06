
import web

render = web.template.render('/home/pi/PASA-2013-TIA-ELA/alameda/brains/html/')

urls = (
    '/', 'index',
	'/motion/detected', 'MotionDetected',
	'/motion/ended', 'MotionEnded'
)

class index:
    def GET(self):
        return render.modesForm()
		
class MotionDetected:
    def GET(self):
        return render.modesForm()
		
class MotionEnded:
    def GET(self):
        return render.modesForm()		

if __name__ == "__main__":
    app = web.application(urls, globals())
    app.run()
