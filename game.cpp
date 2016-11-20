#include <SFML/Graphics.hpp>
#include <windows.h>
#include "resource.h" 

#include "game.hpp"

game::game(sf::RenderWindow *window)
{
	_pWindow = window;

	_shape = sf::RectangleShape(sf::Vector2f(20, 20));
	_shape.setFillColor(sf::Color::Green);

	sf::Texture texture;
	if (!texture.loadFromFile("Top_Down_Survivor\\rifle\\idle\\survivor-idle_rifle_0.png")) 
	{
		throw std::runtime_error("Failed to find resource.");
	}
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

sf::Image game::LoadImageFromResource(const std::string& name)
{
	HRSRC rsrcData = FindResource(NULL, name.c_str(), RT_RCDATA);
	if (!rsrcData)
		throw std::runtime_error("Failed to find resource.");

	DWORD rsrcDataSize = SizeofResource(NULL, rsrcData);
	if (rsrcDataSize <= 0)
		throw std::runtime_error("Size of resource is 0.");

	HGLOBAL grsrcData = LoadResource(NULL, rsrcData);
	if (!grsrcData)
		throw std::runtime_error("Failed to load resource.");

	LPVOID firstByte = LockResource(grsrcData);
	if (!firstByte)
		throw std::runtime_error("Failed to lock resource.");

	sf::Image image;
	if (!image.loadFromMemory(firstByte, rsrcDataSize))
		throw std::runtime_error("Failed to load image from memory.");

	return image;
}
