#include <SFML/Graphics.hpp>
#include "animatedTexture.h"

#include "playerAnimationManager.h"



playerAnimationManager::playerAnimationManager()
{
	_animations[Animations::idle] = animatedTexture("Top_Down_Survivor\\rifle\\idle\\idle.png");
	_animations[Animations::meleeattack] = animatedTexture("Top_Down_Survivor\\rifle\\meleeattack\\meleeattack.png");
	_animations[Animations::move] = animatedTexture("Top_Down_Survivor\\rifle\\move\\move.png");
	_animations[Animations::reload] = animatedTexture("Top_Down_Survivor\\rifle\\reload\\reload.png");
	_animations[Animations::shoot] = animatedTexture("Top_Down_Survivor\\rifle\\shoot\\shoot.png", 0.05F);
	_currentAnimationTexture = _animations[Animations::idle];

	_walkingAnimations[WalkingAnimations::idle] = animatedTexture("Top_Down_Survivor\\feet\\idle\\idle.png");
	_walkingAnimations[WalkingAnimations::run] = animatedTexture("Top_Down_Survivor\\feet\\run\\run.png");
	_walkingAnimations[WalkingAnimations::walk] = animatedTexture("Top_Down_Survivor\\feet\\walk\\walk.png", 0.05F);
	_walkingAnimations[WalkingAnimations::strafe_left] = animatedTexture("Top_Down_Survivor\\feet\\strafe_left\\strafe_left.png", 0.05F);
	_walkingAnimations[WalkingAnimations::strafe_right] = animatedTexture("Top_Down_Survivor\\feet\\strafe_right\\strafe_right.png", 0.05F);
	_currentWalkingAnimationTexture = _walkingAnimations[WalkingAnimations::idle];
}

playerAnimationManager::~playerAnimationManager()
{
}

void playerAnimationManager::update(const float deltaTime, sf::RectangleShape &shape, sf::RectangleShape &feetShape)
{
	if (_currentAnimationTexture.UpdateAnimation(deltaTime))
	{
		shape.setTextureRect(_currentAnimationTexture.StepAnimation());
	}

	if (_currentWalkingAnimationTexture.UpdateAnimation(deltaTime))
	{
		feetShape.setTextureRect(_currentWalkingAnimationTexture.StepAnimation());
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

void playerAnimationManager::setWalkingAnimation(bool isWalking, sf::RectangleShape &walkingShape)
{
	if (isWalking)
	{
		_currentWalkingAnimationTexture = _walkingAnimations[WalkingAnimations::walk];
	}
	else
	{
		_currentWalkingAnimationTexture = _walkingAnimations[WalkingAnimations::idle];
	}
	
	walkingShape.setTexture(&_currentWalkingAnimationTexture.GetTexture());
	walkingShape.setTextureRect(_currentWalkingAnimationTexture.ResetAnimation());
}
