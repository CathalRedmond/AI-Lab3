#include "Operations.h"

sf::Vector2f Operations::getNewVelocity(float t_orientation, sf::Vector2f t_currentVelocity)
{
	float magnitude = getMagnitude(t_currentVelocity);
	float orientation = degreesToRadians(t_orientation);
	return sf::Vector2f(std::cos(orientation), std::sin(orientation)) * magnitude;
}

float Operations::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{
	return getMagnitude(t_velocity) > 0 ? radiansToDegrees((atan2(t_velocity.y, t_velocity.x))) : t_currentOrientation;
}

float Operations::getMagnitude(sf::Vector2f t_vector)
{
	return sqrt(std::pow(t_vector.x, 2) + std::pow(t_vector.y, 2));
}

sf::Vector2f Operations::normalise(sf::Vector2f t_vector)
{
	float magnitude = getMagnitude(t_vector);
	return magnitude > 0 ? t_vector / magnitude : t_vector;
}

float Operations::dotProduct(sf::Vector2f t_vectorOne, sf::Vector2f t_vectorTwo)
{
	return (t_vectorOne.x * t_vectorTwo.x) + (t_vectorOne.y * t_vectorTwo.y);
}

float Operations::radiansToDegrees(float t_angleInRadians)
{
	return t_angleInRadians * (180 / M_PI);
}

float Operations::degreesToRadians(float t_angleInDegrees)
{
	return t_angleInDegrees * (M_PI / 180);
}
