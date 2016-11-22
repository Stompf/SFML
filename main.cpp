#include <SFML/Graphics.hpp>
#include "game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 750), "LunneGame");
	sf::Clock clock;
	game game;

	bool isWindowFocused = true;

	window.setFramerateLimit(60);
	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::GainedFocus:
				isWindowFocused = true;
				break;
			case sf::Event::LostFocus:
				isWindowFocused = false;
				break;
			default:
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			return EXIT_SUCCESS;
		}
		
		game.update(deltaTime.asSeconds(), window);

		window.clear(sf::Color::White);
		
		game.draw(window);
		window.display();
	}

	return EXIT_SUCCESS;
}
