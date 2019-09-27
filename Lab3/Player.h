#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Behaviour.h"

class Player
{
public:
	Player();
	void update();
	void handleInput(sf::Event t_event);
	void render(sf::RenderWindow & t_window);
	MovementData getMovementData();
private:
	void move();
	void screenWrap();
	double getAngleOfRotation();
	void updatePlayerRotation();

	sf::Sprite m_playerSprite;
	sf::Texture m_playerTexture;
	sf::Vector2f m_playerPosition;
	sf::Vector2f m_playerVelocity;
	sf::Vector2f m_playerSize;
	float maxSpeed;
	double angleOfOrientation;

	const double PI;

	bool speedUp;
	bool speedDown;
	bool moveLeft;
	bool moveRight;

	void updateKeyPressed(bool& keyStatus, sf::Event t_event);

	float playerScale = 0.5f;

};

