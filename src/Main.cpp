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

	sf::CircleShape shape(window.getSize().x / 2);
	shape.setFillColor(sf::Color::Red);

	sf::Texture shapeTexture;
	/*shapeTexture.loadFromFile("content/sfml.png");
	shape.setTexture(&shapeTexture);*/

	sf::Font font;
	if (!font.loadFromFile("content/arial_black.ttf"))
	{
		//error
	}

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString("PANIC");

	// set the character size
	text.setCharacterSize(75); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::White);

	// set the text style
	text.setStyle(sf::Text::Bold);

	//article on centering text: https://learnsfml.com/how-to-center-text/

	// get the bounds of the text rectangle
	auto text_width = text.getLocalBounds().width; //auto allows variable to deduce type from the assigned value
	auto text_height = text.getLocalBounds().height;

	text.setPosition(window.getSize().x / 2 - text_width / 2.f, window.getSize().y / 2 - text_height / 2 - 15.f);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			// best explanation of event handline here /Users/katy.garnier/Documents/cpp_projects/sfml-vscode-boilerplate/content/arial_black.ttf
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				std::cout << "Mouse button pressed" << std::endl;
				text.setString("Don't\nPANIC");
				text.setPosition(window.getSize().x / 2 - text_width / 2.f, window.getSize().y / 6.f);
				text.setFillColor(sf::Color::Black);
				shape.setFillColor(sf::Color::Green);
			}
		}

		window.clear();
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}
