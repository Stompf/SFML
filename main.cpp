#include <SFML/Graphics.hpp>
#include "game.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1500, 750), "LunneGame");
	sf::Clock clock;
	game game(&window);

	bool isWindowFocused = true;

	window.setFramerateLimit(60);

	while (window.isOpen())
	{
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

		window.clear(sf::Color::White);

		sf::Time elapsed = clock.restart();
		game.update(elapsed.asSeconds());

		window.display();
	}

	return EXIT_SUCCESS;
}
