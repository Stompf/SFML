#include <SFML/Graphics.hpp>
#include <windows.h>
#include "resource.h" 
#include "game.hpp"

#include "animatedTexture.h"


game::game(sf::RenderWindow *window)
{
	_pWindow = window;

	_shape = sf::RectangleShape(sf::Vector2f(140, 100));

	
	
	
	_animation = new animatedTexture();
	_animation->loadAnimatedTexture("Top_Down_Survivor\\rifle\\idle\\idle.png", "Top_Down_Survivor\\rifle\\idle\\idle.txt");
	//_animation->loadAnimatedTexture("Top_Down_Survivor\\rifle\\meleeattack\\meleeattack.png", "Top_Down_Survivor\\rifle\\meleeattack\\meleeattack.txt");
	_texture = _animation->GetTexture();
	_shape.setTexture(&_texture);
}

game::~game()
{
}

void game::update(float elapsed)
{
	handleInput(_shape, elapsed);
	

	if (_animation->UpdateAnimation(elapsed)) 
	{
		_shape.setTextureRect(_animation->StepAnimation());
	}

	_pWindow->draw(_shape);
}

void game::handleInput(sf::RectangleShape &shape, float elapsed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-(_speed * elapsed), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move((_speed * elapsed), 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0, -(_speed * elapsed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0, (_speed * elapsed));
	}

	if (shape.getPosition().x < 0) {
		shape.setPosition(0, shape.getPosition().y);
	}
	else if (shape.getPosition().x > _pWindow->getView().getSize().x - shape.getSize().x) {
		shape.setPosition(_pWindow->getView().getSize().x - shape.getSize().x, shape.getPosition().y);
	}

	if (shape.getPosition().y < 0) {
		shape.setPosition(shape.getPosition().x, 0);
	}
	else if (shape.getPosition().y > _pWindow->getView().getSize().y - shape.getSize().y) {
		shape.setPosition(shape.getPosition().x, _pWindow->getView().getSize().y - shape.getSize().y);
	}
}