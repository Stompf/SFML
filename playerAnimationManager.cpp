#include <SFML/Graphics.hpp>
#include "animatedTexture.h"

#include "playerAnimationManager.h"



playerAnimationManager::playerAnimationManager()
{
	_animationsRifle[Animations::idle] = animatedTexture("Top_Down_Survivor\\rifle\\idle\\idle.png");
	_animationsRifle[Animations::meleeattack] = animatedTexture("Top_Down_Survivor\\rifle\\meleeattack\\meleeattack.png");
	_animationsRifle[Animations::move] = animatedTexture("Top_Down_Survivor\\rifle\\move\\move.png");
	_animationsRifle[Animations::reload] = animatedTexture("Top_Down_Survivor\\rifle\\reload\\reload.png");
	_animationsRifle[Animations::shoot] = animatedTexture("Top_Down_Survivor\\rifle\\shoot\\shoot.png", 0.05F);

	_animationsHandgun[Animations::idle] = animatedTexture("Top_Down_Survivor\\handgun\\idle\\idle.png");
	_animationsHandgun[Animations::meleeattack] = animatedTexture("Top_Down_Survivor\\handgun\\meleeattack\\meleeattack.png");
	_animationsHandgun[Animations::move] = animatedTexture("Top_Down_Survivor\\handgun\\move\\move.png");
	_animationsHandgun[Animations::reload] = animatedTexture("Top_Down_Survivor\\handgun\\reload\\reload.png");
	_animationsHandgun[Animations::shoot] = animatedTexture("Top_Down_Survivor\\handgun\\shoot\\shoot.png", 0.05F);

	_currentAnimationTexture = _animationsHandgun[Animations::idle];

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

	_currentAnimationTexture = _animationsHandgun[animation];
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
