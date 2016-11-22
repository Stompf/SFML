#pragma once

#include "player.h"

class game
{
public:
	game();
	~game();

	void update(float elapsed, sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);

private:
	player _player;
};

