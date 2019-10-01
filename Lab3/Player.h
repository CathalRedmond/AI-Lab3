#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Operations.h"
#include "ConeOfVision.h"

class Player
{
public:
	Player();
	void update(std::vector<sf::Vector2f> enemyPositions);
	void handleInput(sf::Event t_event);
	void render(sf::RenderWindow & t_window);
	sf::Vector2f getPosition();
private:
	void screenWrap();
	void updatePlayerRotation();
	void updateKeyPressed(bool& t_keyStatus, sf::Event t_event);

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_size;
	const float MAX_SPEED;
	float m_orientation;
	float m_scale;

	bool m_speedUp;
	bool m_speedDown;
	bool m_moveLeft;
	bool m_moveRight;
	bool collisionDetected;

	ConeOfVision cone;
};

