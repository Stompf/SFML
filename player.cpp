#include <SFML/Graphics.hpp>
#include "playerAnimationManager.h"

#include "player.h"

player::player()
{
	_feetShape = sf::RectangleShape(sf::Vector2f(_playerSizeX * 0.4, _playerSizeX * 0.3));
	_feetShape.setOrigin(_feetShape.getSize().x / 2, _feetShape.getSize().y / 2);
	_playerAnimationManager.setWalkingAnimation(false, _feetShape);

	_shape = sf::RectangleShape(sf::Vector2f(_playerSizeX, _playerSizeX * 0.7));
	_shape.setOrigin(_shape.getSize().x / 2, _shape.getSize().y / 2);
	_shape.setPosition(30, 30);

	_playerAnimationManager = playerAnimationManager();
	_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::idle, _shape);
}

player::~player()
{
}

void player::update(const float deltaTime, sf::RenderWindow &window)
{
	sf::Vector2f oldPosition = _shape.getPosition();
	handleInput(deltaTime, window);
	handleAnimation(oldPosition);
	_playerAnimationManager.update(deltaTime, _shape, _feetShape);
}

void player::draw(sf::RenderWindow &window)
{
	window.draw(_feetShape);
	window.draw(_shape);
}

void player::handleInput(float elapsed, sf::RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_shape.move(-(_speed * elapsed), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_shape.move((_speed * elapsed), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_shape.move(0, -(_speed * elapsed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_shape.move(0, (_speed * elapsed));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		_shape.rotate(-_rotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_shape.rotate(_rotationSpeed);
	}

	if (_shape.getPosition().x < 0) {
		_shape.setPosition(0, _shape.getPosition().y);
	}
	else if (_shape.getPosition().x > window.getView().getSize().x - _shape.getSize().x) {
		_shape.setPosition(window.getView().getSize().x - _shape.getSize().x, _shape.getPosition().y);
	}

	if (_shape.getPosition().y < 0) {
		_shape.setPosition(_shape.getPosition().x, 0);
	}
	else if (_shape.getPosition().y > window.getView().getSize().y - _shape.getSize().y) {
		_shape.setPosition(_shape.getPosition().x, window.getView().getSize().y - _shape.getSize().y);
	}

	_feetShape.setPosition(_shape.getPosition());
	_feetShape.setRotation(_shape.getRotation());
}

void player::handleAnimation(sf::Vector2f oldPosition)
{
	bool moving = oldPosition.x != _shape.getPosition().x || oldPosition.y != _shape.getPosition().y;

	if (moving != _isMoving)
	{
		_playerAnimationManager.setWalkingAnimation(moving, _feetShape);
		_isMoving = moving;
	}

	_shape.setScale(1, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::shoot, _shape);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		_shape.setScale(1.05F, 1.05F);
		_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::reload, _shape);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		_shape.setScale(1.15F, 1.75F);
		_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::meleeattack, _shape);
	}
	else
	{
		if (moving)
		{
			_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::move, _shape);
		}
		else if (!moving)
		{
			_playerAnimationManager.setCurrentAnimation(playerAnimationManager::Animations::idle, _shape);
		}
	}


}
