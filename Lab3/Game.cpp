#include "Game.h"

Game::Game():
	seek{sf::Color::Green, sf::Vector2f(100,100)},
	flee{sf::Color::Blue, sf::Vector2f(SCREEN_SIZE::WIDTH / 2, SCREEN_SIZE::HEIGHT / 2)},
	wander{sf::Color::Yellow, sf::Vector2f(100, 700)},
	arrive{sf::Color::Magenta , sf::Vector2f(700, 100)}
{
	m_window.create(sf::VideoMode{ SCREEN_SIZE::WIDTH, SCREEN_SIZE::HEIGHT }, "Lab 1");
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

	seek.update(Behaviour::Seek(m_player.getMovementData(), seek.getMovementData()));
	flee.update(Behaviour::Flee(m_player.getMovementData(), flee.getMovementData()));
	arrive.update(Behaviour::Arrive(m_player.getMovementData(), arrive.getMovementData(), 150 , 0.5, 1.5  ));
	wander.update(Behaviour::Wander(m_player.getMovementData(), wander.getMovementData(), 5));

	m_player.update();
}

void Game::render()
{
	m_window.clear(sf::Color(0,255,255,255));
	seek.render(m_window);
	flee.render(m_window);
	wander.render(m_window);
	arrive.render(m_window);
	m_player.render(m_window);
	m_window.display();
}
