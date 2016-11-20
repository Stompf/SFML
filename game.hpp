#pragma once
class game
{
public:
	game(sf::RenderWindow *window);
	~game();

	void update(float elapsed);
	
private:
	const float _speed = 500;

	sf::RenderWindow *_pWindow;
	sf::RectangleShape _shape;

	void handleInput(sf::RectangleShape &shape, float elapsed);
	sf::Image LoadImageFromResource(const std::string& name);
};

