#pragma once
#include <SFML/Graphics.hpp>
class VectorOperations
{
public:

	static float magnitude(sf::Vector2f t_velocity);
	static sf::Vector2f normalise(sf::Vector2f t_velocity);
};

