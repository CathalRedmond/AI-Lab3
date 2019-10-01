#include "ConeOfVision.h"

ConeOfVision::ConeOfVision(sf::Vector2f t_position, float t_angle, float t_fieldOfView, float coneDisatnce):
	entityPosition{t_position},
	entityAngle{t_angle},
	fieldOfView{t_fieldOfView},
	noCollisionColour{sf::Color(122, 89, 1)},
	collisionColour{sf::Color::Red},
	coneDistance{ coneDisatnce }
{
	cone = sf::VertexArray(sf::Triangles, 3);
	coneVertices.push_back(sf::Vector2f(entityPosition));
	coneVertices.push_back(getOtherPoints(true));
	coneVertices.push_back(getOtherPoints(false));

	for (size_t i = 0; i < coneVertices.size(); i++)
	{
		cone[i].position = coneVertices[i];
		cone[i].color = noCollisionColour;
	}
}

sf::Vector2f ConeOfVision::getOtherPoints(bool t_isLeftPoint)
{
	float angle = t_isLeftPoint ? entityAngle - fieldOfView : entityAngle + fieldOfView;
	angle = Operations::degreesToRadians(angle);
	sf::Vector2f newPoint;
	newPoint.x = coneDistance * (std::cos(angle));
	newPoint.y = coneDistance * (std::sin(angle));
	return newPoint + entityPosition;
}

void ConeOfVision::updateCone(sf::Vector2f t_newPosition, float t_newAngle, bool collision)
{
	entityPosition = t_newPosition;
	entityAngle = t_newAngle;

	coneVertices[0] = entityPosition;
	coneVertices[1] = getOtherPoints(true);
	coneVertices[2] = getOtherPoints(false);

	for (size_t i = 0; i < coneVertices.size(); i++)
	{
		cone[i].position = coneVertices[i];
		cone[i].color = collision ? collisionColour : noCollisionColour;
	}
}

bool ConeOfVision::collisionDetection(sf::Vector2f otherEntityPosition, sf::Vector2f entityVEL)
{
	bool collisionDetected = false;
	sf::Vector2f distBetweenEntities = otherEntityPosition - entityPosition;
	float distPlayer = Operations::getMagnitude(distBetweenEntities);

	if (distPlayer < coneDistance)
	{
		sf::Vector2f unitEntityPosition = Operations::normalise(entityVEL);
		sf::Vector2f unitDistBetweenEntities = Operations::normalise(distBetweenEntities);

		float angle = Operations::dotProduct(unitDistBetweenEntities, unitEntityPosition);

		float angleBetween = std::acos(angle);
		angleBetween = Operations::radiansToDegrees(angleBetween);

		if (angleBetween < fieldOfView) collisionDetected = true;
	}
	return collisionDetected;
}

void ConeOfVision::render(sf::RenderWindow& t_window)
{
	t_window.draw(cone);
}
