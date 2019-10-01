#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Operations.h"
#include <random>

enum class EnemyType
{
	Seek,
	Arrive,
	Wander,
	Flee
};

class Enemy
{
public:
	Enemy(sf::Color t_colour, sf::Vector2f t_position, EnemyType t_type);
	void update(sf::Vector2f t_playerPosition);
	void render(sf::RenderWindow & t_window);
	sf::Vector2f getPosition();
private:
	EnemyType m_type;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_size;
	const float MAX_SPEED;
	const float MAX_ROTATION;
	float m_scale;
	float m_orientation;
	float m_arriveSlowRadius;
	float m_arriveStopRadius;
	sf::Text m_enemyTypeText;
	sf::Font m_font;

	void screenWrap();
	void seek(sf::Vector2f t_playerPosition);
	void flee(sf::Vector2f t_playerPosition);
	void arrive(sf::Vector2f t_playerPosition);
	void wander(sf::Vector2f t_playerPosition);
	void setUpText();
};


