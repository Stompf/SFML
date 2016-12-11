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

	void update(const float deltaTime, sf::RectangleShape &shape, sf::RectangleShape &feetShape);
	void setCurrentAnimation(const Animations animation, sf::RectangleShape &shape);
	Animations getCurrentAnimation();
	void setWalkingAnimation(bool isWalking, sf::RectangleShape &walkingShape);

private:
	enum class WalkingAnimations { idle, walk, run, strafe_left, strafe_right };

	Animations _currentAnimation;
	animatedTexture  _currentAnimationTexture;
	WalkingAnimations _currentWalkingAnimation;
	animatedTexture  _currentWalkingAnimationTexture;
	std::map<Animations, animatedTexture> _animationsRifle;
	std::map<Animations, animatedTexture> _animationsHandgun;
	std::map<WalkingAnimations, animatedTexture> _walkingAnimations;
};

