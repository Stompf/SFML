#pragma once
class animatedTexture
{
public:
	animatedTexture();
	~animatedTexture();
	
	void loadAnimatedTexture(const std::string &pngFile, const std::string &dimensionFile);
	bool UpdateAnimation(const float elapsed);
	sf::IntRect StepAnimation();

	double AnimationSpeed = 0.1;
	sf::Texture GetTexture();

private:
	struct AnimationBbox
	{
		int x;
		int y;
		int width;
		int height;
	};

	sf::Texture _texture;
	std::vector<AnimationBbox> _animations;
	int _currentAnimation = 0;
	float _currentElapsed = 0;

	void readAnimationDimensionFile(const std::string &dimensionFile);
	bool isInteger(const std::string &s);
};

