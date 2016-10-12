#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "game.hpp"

game::game(sf::RenderWindow *window)
{
	_pWindow = window;

	b2Vec2 gravity(0.0f, -10.0f);
	b2World world(gravity);

	_shape = sf::RectangleShape(sf::Vector2f(20, 20));
	_shape.setFillColor(sf::Color::Green);
}

game::~game()
{
}

void game::update(float elapsed)
{
	handleInput(_shape, elapsed);
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
