#include <SFML/Graphics.hpp>
#include <windows.h>
#include "resource.h" 
#include "game.hpp"

game::game()
{
}

game::~game()
{
}

void game::update(float elapsed, sf::RenderWindow &window)
{
	_player.update(elapsed, window);
}

void game::draw(sf::RenderWindow &window)
{
	_player.draw(window);
}
