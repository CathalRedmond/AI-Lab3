#include "Game.h"

Game::Game()
{
	m_window.create(sf::VideoMode{ SCREEN_SIZE::WIDTH, SCREEN_SIZE::HEIGHT }, "Lab 1");
	m_enemys.push_back(new Enemy(sf::Color::Magenta, sf::Vector2f(100, 100), EnemyType::Seek));
	m_enemys.push_back(new Enemy(sf::Color::Green, sf::Vector2f(100, SCREEN_SIZE::HEIGHT - 100), EnemyType::Arrive));
	m_enemys.push_back(new Enemy(sf::Color::Blue, sf::Vector2f(SCREEN_SIZE::WIDTH - 100, 100), EnemyType::Wander));
	m_enemys.push_back(new Enemy(sf::Color::Yellow, sf::Vector2f(SCREEN_SIZE::WIDTH / 2, SCREEN_SIZE::HEIGHT / 2), EnemyType::Flee));
}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
		m_player.handleInput(event);
	}
}

void Game::update(sf::Time t_deltaTime)
{
	std::vector<sf::Vector2f> enemyPositions;

	for (int index = 0; index < m_enemys.size(); index++)
	{
		m_enemys[index]->update(m_player.getPosition());
		enemyPositions.push_back(m_enemys[index]->getPosition());
	}
	m_player.update(enemyPositions);
}

void Game::render()
{
	m_window.clear(sf::Color(0,255,255,255));
	for (int index = 0; index < m_enemys.size(); index++)
	{
		m_enemys[index]->render(m_window);
	}
	m_player.render(m_window);
	m_window.display();
}
