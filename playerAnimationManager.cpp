#include <SFML/Graphics.hpp>
#include "animatedTexture.h"

#include "playerAnimationManager.h"



playerAnimationManager::playerAnimationManager()
{
	_animations[Animations::idle] = animatedTexture("Top_Down_Survivor\\rifle\\idle\\idle.png", "Top_Down_Survivor\\rifle\\idle\\idle.txt");
	_animations[Animations::meleeattack] = animatedTexture("Top_Down_Survivor\\rifle\\meleeattack\\meleeattack.png", "Top_Down_Survivor\\rifle\\meleeattack\\meleeattack.txt");
	_animations[Animations::move] = animatedTexture("Top_Down_Survivor\\rifle\\move\\move.png", "Top_Down_Survivor\\rifle\\move\\move.txt");
	_animations[Animations::reload] = animatedTexture("Top_Down_Survivor\\rifle\\reload\\reload.png", "Top_Down_Survivor\\rifle\\reload\\reload.txt");
	_animations[Animations::shoot] = animatedTexture("Top_Down_Survivor\\rifle\\shoot\\shoot.png", "Top_Down_Survivor\\rifle\\shoot\\shoot.txt", 0.05F);

	_currentAnimationTexture = _animations[Animations::idle];
}

playerAnimationManager::~playerAnimationManager()
{
}

void playerAnimationManager::update(const float deltaTime, sf::RectangleShape &shape)
{
	if (_currentAnimationTexture.UpdateAnimation(deltaTime))
	{
		shape.setTextureRect(_currentAnimationTexture.StepAnimation());
	}
}

void playerAnimationManager::setCurrentAnimation(const Animations animation, sf::RectangleShape &shape)
{
	if (animation == _currentAnimation)
	{
		return;
	}

	_currentAnimationTexture = _animations[animation];
	_currentAnimation = animation;
	shape.setTexture(&_currentAnimationTexture.GetTexture());
	shape.setTextureRect(_currentAnimationTexture.ResetAnimation());
}

playerAnimationManager::Animations playerAnimationManager::getCurrentAnimation()
{
	return _currentAnimation;
}
