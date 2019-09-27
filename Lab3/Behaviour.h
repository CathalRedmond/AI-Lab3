#pragma once
#include <SFML/Graphics.hpp>
#include "VectorOperations.h"
#include <random>
#include <iostream>
static class Behaviour
{
public:

	Behaviour() {}

	static sf::Vector2f getNewVelocity(double t_orientation, sf::Vector2f t_currentVelocity);
	static double getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity);
	static MovementData Seek(sf::Vector2f t_targetPosition, MovementData dataTwo);
	static MovementData Flee(sf::Vector2f t_targetPosition, MovementData dataTwo);
	static MovementData Arrive(sf::Vector2f t_targetPosition, MovementData dataTwo, float radius, float ttl, float maxSpeed);
	static MovementData Wander(sf::Vector2f t_targetPosition, MovementData dataTwo, float maxRotation);
};

