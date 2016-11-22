#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "animatedTexture.h"

animatedTexture::animatedTexture(const std::string &pngFile, const float animationSpeed)
{
	loadAnimatedTexture(pngFile);
	AnimationSpeed = animationSpeed;
}

animatedTexture::animatedTexture()
{
}


animatedTexture::~animatedTexture()
{
}

bool animatedTexture::UpdateAnimation(const float elapsed)
{
	_currentElapsed += elapsed;
	if (_currentElapsed >= AnimationSpeed) {
		_currentElapsed = 0;
		return true;
	}
	return false;
}

sf::IntRect animatedTexture::ResetAnimation()
{
	_currentAnimation = 0;
	_currentElapsed = 0;
	AnimationBbox bbox = _animations[_currentAnimation];
	return sf::IntRect(bbox.x, bbox.y, bbox.width, bbox.height);
}

sf::IntRect animatedTexture::StepAnimation()
{
	_currentAnimation++;

	if ((unsigned)_currentAnimation >= _animations.size())
	{
		_currentAnimation = 0;
	}
	AnimationBbox bbox = _animations[_currentAnimation];
	return sf::IntRect(bbox.x, bbox.y, bbox.width, bbox.height);
}

sf::Texture& animatedTexture::GetTexture()
{
	return _texture;
}

void animatedTexture::loadAnimatedTexture(const std::string &pngFile)
{
	if (!_texture.loadFromFile(pngFile))
	{
		throw std::runtime_error("Failed to find resource: " + pngFile);
	}

	std::string txtFile = pngFile;
	replaceAll(txtFile, ".png", ".txt");
	readAnimationDimensionFile(txtFile);
}


void animatedTexture::readAnimationDimensionFile(const std::string &dimensionFile)
{
	std::ifstream file(dimensionFile);
	std::string str;
	while (std::getline(file, str))
	{
		std::stringstream lineStream(str);
		std::string split;
		std::vector<int> dimensions;
		while (std::getline(lineStream, split, ' ')) 
		{
			if (isInteger(split)) 
			{
				dimensions.push_back(std::stoi(split));
			}
		}
		
		AnimationBbox bbox;
		bbox.x = dimensions[0];
		bbox.y = dimensions[1];
		bbox.width = dimensions[2];
		bbox.height = dimensions[3];

		_animations.push_back(bbox);
	}
}

bool animatedTexture::isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

void animatedTexture::replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}
