#include "VectorOperations.h"

float VectorOperations::magnitude(sf::Vector2f t_velocity)
{
	return sqrt(std::pow(t_velocity.x, 2) + std::pow(t_velocity.y, 2));
}

sf::Vector2f VectorOperations::normalise(sf::Vector2f t_velocity)
{
	float mag = magnitude(t_velocity);
	return mag > 0 ? sf::Vector2f(t_velocity.x / mag, t_velocity.y / mag) : t_velocity;
}