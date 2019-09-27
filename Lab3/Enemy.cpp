#include "enemy.h"

Enemy::Enemy(sf::Color t_colour, sf::Vector2f t_position):
	m_position{t_position},
	MAX_SPEED{1.5f},
	MAX_ROTATION{5.0f},
	m_scale{0.25f},
	m_orientation{0}
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Spaceship.png"))
	{
		throw "Error Loading Enemy Texture";
	}
	m_sprite.setTexture(m_texture);
	m_size = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setColor(t_colour);
}
//
//void Enemy::update(MovementData t_data)
//{
//	m_velocity = t_data.getVelocity() * MAX_SPEED;
//	m_sprite.setRotation(t_data.getAngle());
//	m_position += m_velocity;
//	screenWrap();
//	m_sprite.setPosition(m_position);
//}

void Enemy::update(sf::Vector2f t_playerPosition, EnemyType t_type)
{
	switch (t_type)
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
	}

}



void Enemy::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
}

MovementData Enemy::getMovementData()
{
	return MovementData(m_velocity, m_sprite.getRotation(), m_position);
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
	m_velocity = VectorOperations::normalise(m_velocity);
	m_velocity *= MAX_SPEED;
	m_orientation = Behaviour::getNewOrientation(m_orientation, m_velocity);
}

void Enemy::flee(sf::Vector2f t_playerPosition)
{
	m_velocity = m_position - t_playerPosition;
	m_velocity = VectorOperations::normalise(m_velocity);
	m_velocity *= MAX_SPEED;
	m_orientation = Behaviour::getNewOrientation(m_orientation, m_velocity);
}

void Enemy::arrive(sf::Vector2f t_playerPosition)
{
	float radius = 150;

	float stopRadius = 150;
	float slowRadius = stopRadius * 3;


	sf::Vector2f newVelocity;
	float orientation;

	newVelocity = t_playerPosition - m_position;

	float magnitude = VectorOperations::magnitude
	if (VectorOperations::magnitude(newVelocity) < radius)
	{
		newVelocity = sf::Vector2f(0, 0);
	}
	else if ()
	{

	}
}

void Enemy::wander(sf::Vector2f t_playerPosition)
{
	float maxRotation = 5.0f;
	seek(t_playerPosition);
	m_velocity / MAX_SPEED;

	std::mt19937 range;
	range.seed(std::random_device()());
	std::uniform_int_distribution<int> randomNumber(-1, 1);

	m_orientation += maxRotation * randomNumber(range);
	m_velocity = Behaviour::getNewVelocity(m_orientation, m_velocity);
	m_velocity* MAX_SPEED;
}
