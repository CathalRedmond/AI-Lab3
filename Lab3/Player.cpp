#include "Player.h"

Player::Player():
	m_speedUp{ false },
	m_speedDown{ false },
	m_moveLeft{ false },
	m_moveRight{ false },
	MAX_SPEED{25},
	m_velocity{sf::Vector2f(4,4)},
	m_position{sf::Vector2f(SCREEN_SIZE::WIDTH /2 , SCREEN_SIZE::HEIGHT / 2)},
	m_orientation{Operations::getNewOrientation(0, m_velocity)},
	m_scale{0.5f},

	cone{ m_position, m_orientation, 25 , 250}
{
	if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Spaceship.png"))
	{
		throw "Error Loading Player Texture";
	}
	m_sprite.setTexture(m_texture);
	m_size = sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	m_sprite.setScale(m_scale, m_scale);
	collisionDetected = false;
}

void Player::update(std::vector<sf::Vector2f> enemyPositions)
{
	if (m_speedUp)
	{
		sf::Vector2f newVelocity;
		float magnitude = Operations::getMagnitude(m_velocity);

		newVelocity = magnitude > 0 ? Operations::normalise(m_velocity) :
		sf::Vector2f(std::cos(Operations::degreesToRadians(m_orientation)), std::sin(Operations::degreesToRadians(m_orientation)));

		m_velocity += newVelocity;

		if (MAX_SPEED < Operations::getMagnitude(m_velocity))
			m_velocity = newVelocity * MAX_SPEED;
	}
	else if (m_speedDown)
	{
		m_velocity *= 0.9f;
		if (0.1f > Operations::getMagnitude(m_velocity))
			m_velocity = sf::Vector2f();
	}
	if (m_moveLeft)
	{
		m_orientation -= 2;
		updatePlayerRotation();
	}
	else if (m_moveRight)
	{
		m_orientation += 2;
		updatePlayerRotation();
	}
	m_position += m_velocity;
	screenWrap();
	m_sprite.setPosition(m_position);

	cone.updateCone(m_position, m_orientation, collisionDetected);
	collisionDetected = false;

	for (size_t i = 0; i < enemyPositions.size(); i++)
	{
		if (cone.collisionDetection(enemyPositions[i], m_velocity))
		{
			collisionDetected = true;
		}
	}
}

void Player::handleInput(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::W || t_event.key.code == sf::Keyboard::Up)
	{
		updateKeyPressed(m_speedUp, t_event);
	}
	else if (t_event.key.code == sf::Keyboard::S || t_event.key.code == sf::Keyboard::Down)
	{
		updateKeyPressed(m_speedDown, t_event);
	}
	if (t_event.key.code == sf::Keyboard::A || t_event.key.code == sf::Keyboard::Left)
	{
		updateKeyPressed(m_moveLeft, t_event);
	}
	else if (t_event.key.code == sf::Keyboard::D || t_event.key.code == sf::Keyboard::Right)
	{
		updateKeyPressed(m_moveRight, t_event);
	}
}

void Player::updateKeyPressed(bool& t_keyStatus, sf::Event t_event)
{
	bool isKeyPressed = t_event.type == sf::Event::KeyPressed;
	bool isKeyReleased = t_event.type == sf::Event::KeyReleased;
	
	if (isKeyPressed) t_keyStatus = true;
	else if (isKeyReleased) t_keyStatus = false;
}

void Player::screenWrap()
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

void Player::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_sprite);
	cone.render(t_window);
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

void Player::updatePlayerRotation()
{
	if (m_orientation < 0) m_orientation = 360;
	else if (m_orientation > 360) m_orientation = 0;
	m_sprite.setRotation(m_orientation);
	m_velocity = Operations::getNewVelocity(m_orientation, m_velocity);
}
