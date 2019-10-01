#pragma once
#define _USE_MATH_DEFINES
#include<SFML/Graphics.hpp>
#include <iostream>
#include<cmath>

static class Operations
{
public:
	static sf::Vector2f getNewVelocity(float t_orientation, sf::Vector2f t_currentVelocity);
	static float getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity);
	static float getMagnitude(sf::Vector2f t_vector);
	static sf::Vector2f normalise(sf::Vector2f t_vector);
	static float dotProduct(sf::Vector2f t_vectorOne, sf::Vector2f t_vectorTwo);
	static float radiansToDegrees(float t_angleInRadians);
	static float degreesToRadians(float t_angleInDegrees);
};

