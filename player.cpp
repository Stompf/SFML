#include <SFML/Graphics.hpp>
#include "playerAnimationManager.h"

#include "player.h"

player::player()
{
	_shape = sf::RectangleShape(sf::Vector2f(70, 50));

	_playerAnimationManager = playerAnimationManager();
	_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::idle, _shape);
}

player::~player()
{
}

void player::update(const float deltaTime, sf::RenderWindow &window)
{
	handleInput(_shape, deltaTime, window);
	_playerAnimationManager.update(deltaTime, _shape);
}

void player::draw(sf::RenderWindow &window)
{
	window.draw(_shape);
}

void player::handleInput(sf::RectangleShape &shape, float elapsed, sf::RenderWindow &window)
{
	bool moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-(_speed * elapsed), 0);
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move((_speed * elapsed), 0);
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0, -(_speed * elapsed));
		moving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0, (_speed * elapsed));
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		_shape.rotate(_rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_shape.rotate(-_rotationSpeed);
	}

	if(moving && _playerAnimationManager.getCurrentAnimation() == playerAnimationManager::Animations::idle)
	{
		_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::move, _shape);
	}
	else if (!moving && _playerAnimationManager.getCurrentAnimation() == playerAnimationManager::Animations::move)
	{
		_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::idle, _shape);
	}

	if (shape.getPosition().x < 0) {
		shape.setPosition(0, shape.getPosition().y);
	}
	else if (shape.getPosition().x > window.getView().getSize().x - shape.getSize().x) {
		shape.setPosition(window.getView().getSize().x - shape.getSize().x, shape.getPosition().y);
	}

	if (shape.getPosition().y < 0) {
		shape.setPosition(shape.getPosition().x, 0);
	}
	else if (shape.getPosition().y > window.getView().getSize().y - shape.getSize().y) {
		shape.setPosition(shape.getPosition().x, window.getView().getSize().y - shape.getSize().y);
	}

	
}
