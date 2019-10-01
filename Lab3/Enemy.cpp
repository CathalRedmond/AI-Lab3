#include "enemy.h"

Enemy::Enemy(sf::Color t_colour, sf::Vector2f t_position, EnemyType t_type):
	m_position{t_position},
	MAX_SPEED{1.5f},
	MAX_ROTATION{5.0f},
	m_scale{0.5f},
	m_orientation{0},
	m_arriveStopRadius{75},
	m_type{t_type}
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Spaceship.png"))
	{
		throw "Error Loading Enemy Texture";
	}
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		throw "Error Loading Enemy Font";
	}
	m_arriveSlowRadius = m_arriveStopRadius * 3;
	m_sprite.setTexture(m_texture);
	m_size = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setColor(t_colour);
	setUpText();
}

void Enemy::update(sf::Vector2f t_playerPosition)
{
	switch (m_type)
	{
		case EnemyType::Seek:
			seek(t_playerPosition);
			break;
		case EnemyType::Arrive:
			arrive(t_playerPosition);
			break;
		case EnemyType::Wander:
			wander(t_playerPosition);
			break;
		case EnemyType::Flee:
			flee(t_playerPosition);
			break;
		default:
			break;
	}/*
	m_position += m_velocity;
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	m_enemyTypeText.setPosition(m_position.x + 20, m_position.y);*/
}

void Enemy::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
	t_window.draw(m_enemyTypeText);
}

sf::Vector2f Enemy::getPosition()
{
	return m_position;
}

void Enemy::screenWrap()
{
	if (m_position.x < -m_size.x / 2)
		m_position.x = SCREEN_SIZE::WIDTH;
	else if (m_position.x > SCREEN_SIZE::WIDTH + m_size.x / 2)
		m_position.x = 0;

	if (m_position.y < -m_size.y / 2)
		m_position.y = SCREEN_SIZE::HEIGHT;
	else if (m_position.y > SCREEN_SIZE::HEIGHT + m_size.y / 2)
		m_position.y = 0;
}

void Enemy::seek(sf::Vector2f t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	m_velocity = Operations::normalise(m_velocity);
	m_velocity *= MAX_SPEED;
	m_orientation = Operations::getNewOrientation(m_orientation, m_velocity);
}

void Enemy::flee(sf::Vector2f t_playerPosition)
{
	m_velocity = m_position - t_playerPosition;
	m_velocity = Operations::normalise(m_velocity);
	m_velocity *= MAX_SPEED;
	m_orientation = Operations::getNewOrientation(m_orientation, m_velocity);
}

void Enemy::arrive(sf::Vector2f t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	float magnitude = Operations::getMagnitude(m_velocity);

	if (magnitude < m_arriveSlowRadius)
	{
		if (magnitude < m_arriveStopRadius)
		{
			m_velocity = sf::Vector2f();
		}
		else
		{
			if (MAX_SPEED < magnitude)
			{
				m_velocity = Operations::normalise(m_velocity);
				m_velocity* MAX_SPEED;
			}
			m_velocity /= (magnitude / m_arriveSlowRadius);
		}
	}
	else
	{
		if (MAX_SPEED < magnitude)
		{
			m_velocity = Operations::normalise(m_velocity);
			m_velocity* MAX_SPEED;
		}
	}
	m_orientation = Operations::getNewOrientation(m_orientation, m_velocity);
}

void Enemy::wander(sf::Vector2f t_playerPosition)
{
	m_velocity = t_playerPosition - m_position;
	m_velocity = Operations::normalise(m_velocity);
	m_orientation = Operations::getNewOrientation(m_orientation, m_velocity);

	std::mt19937 range;
	range.seed(std::random_device()());
	std::uniform_int_distribution<int> randomNumber(-1, 1);

	m_orientation += MAX_ROTATION * randomNumber(range);
	m_velocity = Operations::getNewVelocity(m_orientation, m_velocity) / Operations::getMagnitude(m_velocity);
	m_velocity* MAX_SPEED;
}

void Enemy::setUpText()
{
	m_enemyTypeText.setFont(m_font);
	m_enemyTypeText.setCharacterSize(32);
	switch (m_type)
	{
	case EnemyType::Seek:
		m_enemyTypeText.setString("SEEK");
		break;
	case EnemyType::Arrive:
		m_enemyTypeText.setString("ARRIVE");
		break;
	case EnemyType::Wander:
		m_enemyTypeText.setString("WANDER");
		break;
	case EnemyType::Flee:
		m_enemyTypeText.setString("FLEE");
		break;
	default:
		break;
	}
}
