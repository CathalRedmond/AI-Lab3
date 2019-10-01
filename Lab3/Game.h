#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public :
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;
	Player m_player;

	std::vector<Enemy*> m_enemys;

};

