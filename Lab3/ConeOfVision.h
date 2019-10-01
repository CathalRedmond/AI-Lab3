#pragma once
#include <SFML/Graphics.hpp>
#include "Operations.h"

static const struct VERTEX_POINT
{

};

class ConeOfVision
{
public:
	ConeOfVision(sf::Vector2f t_position, float t_angle, float t_fieldOfView, float coneDisatnce);
	sf::VertexArray cone;

	std::vector<sf::Vector2f> coneVertices;

	float coneDistance;
	float fieldOfView;
	float entityAngle;
	sf::Vector2f entityPosition;

	sf::Vector2f getOtherPoints(bool t_isLeftPoint);

	void updateCone(sf::Vector2f t_newPosition, float t_newAngle, bool collision);

	bool collisionDetection(sf::Vector2f otherEntityPosition, sf::Vector2f entityVEL);

	sf::Color noCollisionColour;
	sf::Color collisionColour;

	void render(sf::RenderWindow& t_window);
};

