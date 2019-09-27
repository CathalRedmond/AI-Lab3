#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Behaviour.h"

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
	Enemy(sf::Color t_colour, sf::Vector2f t_position);
	void update(sf::Vector2f t_playerPosition, EnemyType t_type);
	void render(sf::RenderWindow & t_window);
private:
	void screenWrap();
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_size;
	const float MAX_SPEED;
	float m_scale;
	float m_orientation;

	void seek(sf::Vector2f t_playerPosition);
	void flee(sf::Vector2f t_playerPosition);
	void arrive(sf::Vector2f t_playerPosition);
	void wander(sf::Vector2f t_playerPosition);
};


