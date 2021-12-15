#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	// Use the screenScalingFactor
	window.create(sf::VideoMode(300.0f * screenScalingFactor, 300.0f * screenScalingFactor), "SFML works!");
	platform.setIcon(window.getSystemHandle());

	//create a circle the size of the window and set the fill color
	sf::CircleShape shape(window.getSize().x / 2);
	shape.setFillColor(sf::Color::Red);

	//load a font - must be in your project directory!
	sf::Font font;
	if (!font.loadFromFile("content/arial_black.ttf"))
	{
		//error
	}

	//create a text object
	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString("PANIC");

	// set the character size
	text.setCharacterSize(75); // in pixels, not points!

	// set the text color
	text.setFillColor(sf::Color::White);

	// set the text style
	text.setStyle(sf::Text::Bold);

	//article on centering text (it's complicated): https://learnsfml.com/how-to-center-text/

	// get the bounds of the text rectangle
	auto text_width = text.getLocalBounds().width; //auto allows variable to deduce type from the assigned value
	auto text_height = text.getLocalBounds().height;

	//set the position of the text (attempted to center it!)
	text.setPosition(window.getSize().x / 2 - text_width / 2.f, window.getSize().y / 2 - text_height / 2 - 15.f);

	//create an event object
	sf::Event event;

	//this loop runs as long as the windo is opened
	while (window.isOpen())
	{
		//this loop is listening for events
		while (window.pollEvent(event))
		{
			//if user clicks the close window button, close the window
			if (event.type == sf::Event::Closed)
				window.close();

			// good explanation of event handling here
			//if user clicks window with mouse
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				std::cout << "Mouse button pressed" << std::endl;
				//change the text
				text.setString("Don't\nPANIC");
				//change position to accomdate new text size
				text.setPosition(window.getSize().x / 2 - text_width / 2.f, window.getSize().y / 6.f);
				//change text color
				text.setFillColor(sf::Color::Black);
				//change circle color
				shape.setFillColor(sf::Color::Green);
			}
		}

		//this is like pygame, where we redraw the screen every time through the loop
		//clear the window
		window.clear();
		//draw the circle
		window.draw(shape);
		//draw the text
		window.draw(text);
		//refresh the windwo with the drawings
		window.display();
	}

	return 0;
}
