#pragma once
class animatedTexture
{
public:
	animatedTexture(const std::string &pngFile, const std::string &dimensionFile);
	animatedTexture();
	~animatedTexture();

	bool UpdateAnimation(const float elapsed);
	sf::IntRect ResetAnimation();
	sf::IntRect StepAnimation();

	double AnimationSpeed = 0.05;
	sf::Texture& GetTexture();

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

	void loadAnimatedTexture(const std::string &pngFile, const std::string &dimensionFile);
	void readAnimationDimensionFile(const std::string &dimensionFile);
	bool isInteger(const std::string &s);
};

