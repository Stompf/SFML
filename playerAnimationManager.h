#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "animatedTexture.h"

class playerAnimationManager
{
public:
	playerAnimationManager();
	~playerAnimationManager();

	enum class Animations { idle, meleeattack, move, reload, shoot };

	void update(const float deltaTime, sf::RectangleShape &shape);
	void setCurrentAnimation(const Animations animation, sf::RectangleShape &shape);
	Animations getCurrentAnimation();

private:
	Animations _currentAnimation;
	animatedTexture  _currentAnimationTexture;
	std::map<Animations, animatedTexture> _animations;
};

