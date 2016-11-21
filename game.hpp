#pragma once
#include "animatedTexture.h"

class game
{
public:
	game(sf::RenderWindow *window);
	~game();

	void update(float elapsed);
	void draw();

private:
	const float _speed = 100;
	animatedTexture *_animation;

	sf::RenderWindow *_pWindow;
	sf::RectangleShape _shape;
	sf::Texture _texture;

	void handleInput(sf::RectangleShape &shape, float elapsed);
};

