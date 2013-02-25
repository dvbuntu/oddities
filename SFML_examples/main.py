import math
import sfml

window = sfml.RenderWindow(sfml.VideoMode(800, 600), "SFML Example")

font = sfml.Font.load_from_file("../resources/DejaVuSans.ttf")

# create text to display
text = sfml.Text("SFML!!!", font, 32)
text.color = sfml.Color.BLACK
# center text
bounds = text.local_bounds
text.origin = (bounds.width / 2, bounds.height / 2)
text.position = window.default_view.center

# create fps text
fps = sfml.Text("", font, 12)
fps.color = sfml.Color(127, 127, 127)
fps.position = (10, 10)

timer = sfml.Clock() # for measuring time per frame
clock = sfml.Clock() # for measuring overall time

while window.open:
	# iterate over input events since last frame
	for event in window.iter_events():
		# clicking the OS's close button or pressing escape
		if event.type == sfml.Event.CLOSED or (event.type == sfml.Event.KEY_PRESSED and event.code == sfml.Keyboard.ESCAPE):
			window.close()
		# left clicking
		elif event.type == sfml.Event.MOUSE_BUTTON_PRESSED and event.button == sfml.Mouse.LEFT:
			text.position = sfml.Mouse.get_position(window)

	# crazy-ass transforms
	time = clock.elapsed_time.as_seconds()
	text.rotation = math.sin(time) * 45
	text.scale = (math.cos(time / 2), math.cos(time / 3))

	time = timer.elapsed_time.as_seconds()
	timer.restart()

	# update FPS text
	fps.string = "{0} FPS".format(int(1 / time))

	# draw everything to the window
	window.clear(sfml.Color.WHITE)
	window.draw(text)
	window.draw(fps)

	# refresh the window
	window.display()
