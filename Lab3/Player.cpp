#include "Player.h"

Player::Player():
	PI{ 3.14159 },
	speedUp{ false },
	speedDown{ false },
	moveLeft{ false },
	moveRight{ false }
	
{
	if (!m_playerTexture.loadFromFile("ASSETS\\IMAGES\\Spaceship.png"))
	{
		throw "Error Loading Player Texture";
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSize = sf::Vector2f(m_playerSprite.getGlobalBounds().width, m_playerSprite.getGlobalBounds().height);
	m_playerSprite.setOrigin(m_playerSize.x / 2, m_playerSize.y / 2);
	m_playerVelocity = sf::Vector2f(4, 4);
	m_playerPosition = sf::Vector2f(SCREEN_SIZE::WIDTH - 100, SCREEN_SIZE::HEIGHT - 100);
	m_playerSprite.setPosition(m_playerPosition);
	angleOfOrientation = getAngleOfRotation();
	m_playerSprite.setRotation(angleOfOrientation);
	maxSpeed = 25;
	m_playerSprite.setScale(playerScale, playerScale);
}

void Player::update()
{
	if (speedUp)
	{
		sf::Vector2f newVelocity;
		double magnitude = sqrt(std::pow(m_playerVelocity.x, 2) + std::pow(m_playerVelocity.y, 2));
		bool isMagnitudeValid = magnitude > 0;

		newVelocity.x = isMagnitudeValid ? m_playerVelocity.x / magnitude : std::cos(angleOfOrientation * (PI / 180));
		newVelocity.y = isMagnitudeValid ? m_playerVelocity.y / magnitude : std::sin(angleOfOrientation * (PI / 180));

		m_playerVelocity += newVelocity;
		if (maxSpeed < sqrt(std::pow(m_playerVelocity.x, 2) + std::pow(m_playerVelocity.y, 2)))
			m_playerVelocity = newVelocity * maxSpeed;
	}
	else if (speedDown)
	{
		m_playerVelocity *= 0.9f;
		if (0.1f > sqrt(std::pow(m_playerVelocity.x, 2) + std::pow(m_playerVelocity.y, 2)))
			m_playerVelocity = sf::Vector2f(0, 0);
	}
	if (moveLeft)
	{
		angleOfOrientation -= 2;
		updatePlayerRotation();
	}
	else if (moveRight)
	{
		angleOfOrientation += 2;
		updatePlayerRotation();
	}
	m_playerPosition += m_playerVelocity;
	screenWrap();
	m_playerSprite.setPosition(m_playerPosition);
}

void Player::handleInput(sf::Event t_event)
{
	if (t_event.key.code == sf::Keyboard::W || t_event.key.code == sf::Keyboard::Up)
	{
		updateKeyPressed(speedUp, t_event);
	}
	else if (t_event.key.code == sf::Keyboard::S || t_event.key.code == sf::Keyboard::Down)
	{
		updateKeyPressed(speedDown, t_event);
	}
	if (t_event.key.code == sf::Keyboard::A || t_event.key.code == sf::Keyboard::Left)
	{
		updateKeyPressed(moveLeft, t_event);
	}
	else if (t_event.key.code == sf::Keyboard::D || t_event.key.code == sf::Keyboard::Right)
	{
		updateKeyPressed(moveRight, t_event);
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
	if (m_playerPosition.x < -m_playerSize.x / 2)
		m_playerPosition.x = SCREEN_SIZE::WIDTH;
	else if (m_playerPosition.x > SCREEN_SIZE::WIDTH + m_playerSize.x / 2)
		m_playerPosition.x = 0;

	if (m_playerPosition.y < -m_playerSize.y / 2)
		m_playerPosition.y = SCREEN_SIZE::HEIGHT;
	else if (m_playerPosition.y > SCREEN_SIZE::HEIGHT + m_playerSize.y / 2)
		m_playerPosition.y = 0;
}

void Player::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_playerSprite);
}

MovementData Player::getMovementData()
{
	return MovementData(m_playerVelocity, angleOfOrientation, m_playerPosition);
}

double Player::getAngleOfRotation()
{
	float angleInRadians = std::atan2((m_playerVelocity.y), m_playerVelocity.x);
	angleInRadians = angleInRadians;
	return (angleInRadians * (180 / 3.14));
}

void Player::updatePlayerRotation()
{
	if (angleOfOrientation < 0) angleOfOrientation = 360;
	else if (angleOfOrientation > 360) angleOfOrientation = 0;
	m_playerSprite.setRotation(angleOfOrientation);
	m_playerVelocity = Behaviour::getNewVelocity(angleOfOrientation, m_playerVelocity);
}
