#include "Behaviour.h"

sf::Vector2f Behaviour::getNewVelocity(double t_orientation, sf::Vector2f t_currentVelocity)
{

	double magnitude = sqrt(std::pow(t_currentVelocity.x, 2) + std::pow(t_currentVelocity.y, 2));

	double orientationInRadians = t_orientation * (3.14159 / 180);

	double x = std::cos(orientationInRadians) * magnitude;
	double y = std::sin(orientationInRadians) * magnitude;
		 

	return sf::Vector2f(x,y);
}

double Behaviour::getNewOrientation(float t_currentOrientation, sf::Vector2f t_velocity)
{
	return VectorOperations::magnitude(t_velocity) > 0 ? (atan2(t_velocity.y, t_velocity.x) )* (180/3.14159) : t_currentOrientation;
}

MovementData Behaviour::Seek(sf::Vector2f t_targetPosition, MovementData currentData)
{
	sf::Vector2f newVelocity;
	float orientation;

	newVelocity = targetData.getPosition() - currentData.getPosition();
	newVelocity = VectorOperations::normalise(newVelocity);
	orientation = getNewOrientation(currentData.getAngle(), currentData.getVelocity());


	return MovementData(newVelocity, orientation, currentData.getPosition());
}

MovementData Behaviour::Flee(sf::Vector2f t_targetPosition, MovementData dataTwo)
{
	sf::Vector2f newVelocity;
	float orientation;

	newVelocity = dataTwo.getPosition() - dataOne.getPosition() ;
	newVelocity = VectorOperations::normalise(newVelocity);
	orientation = getNewOrientation(dataTwo.getAngle(), dataTwo.getVelocity());


	return MovementData(newVelocity, orientation, dataTwo.getPosition());
}

MovementData Behaviour::Arrive(sf::Vector2f t_targetPosition, MovementData dataTwo, float radius, float ttl, float maxSpeed)
{
	sf::Vector2f newVelocity;
	float orientation;

	newVelocity = dataOne.getPosition() - dataTwo.getPosition();



	if (VectorOperations::magnitude(newVelocity) < radius)
	{
		return MovementData(sf::Vector2f(0,0), dataTwo.getAngle(), dataTwo.getPosition());
	}
	newVelocity = newVelocity / ttl;
	if (VectorOperations::magnitude(newVelocity) > maxSpeed)
	{
		newVelocity = VectorOperations::normalise(newVelocity);
	}
	orientation = getNewOrientation(dataTwo.getAngle(), dataTwo.getVelocity());


	return MovementData(newVelocity, orientation, dataTwo.getPosition());
}

MovementData Behaviour::Wander(sf::Vector2f t_targetPosition, MovementData dataTwo, float maxRotation)
{
	sf::Vector2f newVelocity;
	float orientation;

	newVelocity = dataOne.getPosition() - dataTwo.getPosition();
	newVelocity = VectorOperations::normalise(newVelocity);
	orientation = getNewOrientation(dataTwo.getAngle(), dataTwo.getVelocity());

	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<int> randomNum(-1, 1);
	int randNum = randomNum(rng);
	orientation += (maxRotation * randNum);
	newVelocity = getNewVelocity(orientation, newVelocity);

	return MovementData(newVelocity, orientation, dataTwo.getPosition());
}


