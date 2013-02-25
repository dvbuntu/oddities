#!/usr/bin/env ruby

require 'sfml/all'

window = SFML::RenderWindow.new(SFML::VideoMode.new(800, 600), "SFML Example")

font = SFML::Font.new
font.load_from_file("../resources/DejaVuSans.ttf")

# create text to display
text = SFML::Text.new("SFML!!!", font, 32)
text.color = SFML::Color::Black
# center text
bounds = text.local_bounds
text.origin = [bounds.width / 2, bounds.height / 2]
text.position = window.default_view.center

# create fps text
fps = SFML::Text.new("", font, 12)
fps.color = SFML::Color.new(127, 127, 127)
fps.position = [10, 10]

timer = SFML::Clock.new
clock = SFML::Clock.new

while window.open?
	# iterate over inputs events since last frame
	window.each_event do |event|
		if event.type == SFML::Event::Closed or (event.type == SFML::Event::KeyPressed and event.key.code == SFML::Keyboard::Escape)
			window.close
		elsif event.type == SFML::Event::MouseButtonPressed and event.mouse_button.button == SFML::Mouse::Left
			text.position = SFML::Mouse::position(window)
		end
	end

	# crazy-ass transform
	time = clock.time.as_seconds
	text.rotation = Math::sin(time) * 45
	text.scale = [Math::cos(time / 2), Math::cos(time / 3)]

	time = timer.elapsed_time.as_seconds
	timer.restart

	# update FPS text
	fps.string = "#{(1 / time).to_i} FPS"

	# draw everything to the window
	window.clear SFML::Color::White
	window.draw text
	window.draw fps

	# refresh the window
	window.display
end
