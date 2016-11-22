#pragma once
#include "playerAnimationManager.h"

class player
{
public:
	player();
	~player();


	void update(const float deltaTime, sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
private:
	const float _speed = 100;
	const float _rotationSpeed = 2;
	bool _isMoving;
	playerAnimationManager _playerAnimationManager;
	sf::RectangleShape _shape;
	sf::RectangleShape _feetShape;

	void handleInput(float elapsed, sf::RenderWindow &window);
	void handleAnimation(sf::Vector2f oldPosition);
};

