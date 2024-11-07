#include "Game.h"


Game::Game()
{
	backgroud_texture_.loadFromFile("Assets/Background.png");
	backgroud_move_texture.loadFromFile("Assets/Background_move.png");

	background_.setTexture(backgroud_texture_);
	background_.setScale(1.2f, 1.2f);
	background_move_1.setTexture(backgroud_move_texture);
	background_move_1.setScale(1.2f, 1.2f);
	background_move_1.setColor(sf::Color(255, 255, 255, 100));
	background_move_2.setTexture(backgroud_move_texture);
	background_move_2.setScale(1.2f, 1.2f);
	background_move_2.setColor(sf::Color(255, 255, 255, 100));

	window.create(sf::VideoMode(background_.getGlobalBounds().width, background_.getGlobalBounds().height), "Space Shooter !!!");

	player_.SetPosition({ static_cast<float>(window.getSize().x) / 2,static_cast<float>(window.getSize().y / 6) * 5 });

	background_move_2.setPosition(0, -static_cast<int>(window.getSize().y));
}

 
void Game::Loop()
{
	while (window.isOpen())
	{
		if(background_move_1.getPosition().y >= window.getSize().y)
		{
			background_move_1.setPosition(0, -static_cast<int>(window.getSize().y));
			background_move_2.setPosition(0, 0);
		}
		else if(background_move_2.getPosition().y >= window.getSize().y)
		{
			background_move_2.setPosition(0, -static_cast<int>(window.getSize().y));
			background_move_1.setPosition(0, 0);
		}

		background_move_1.setPosition(background_move_1.getPosition().x, background_move_1.getPosition().y + 0.2);
		background_move_2.setPosition(background_move_2.getPosition().x, background_move_2.getPosition().y + 0.2);

		window.clear();

		sf::Event event;
           		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player_.Move(sf::Vector2f(0, -1), dt_game_, window.getSize());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player_.Move(sf::Vector2f(0, 1), dt_game_, window.getSize());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player_.Idle(idle_fram_);
			reimu_turn_ = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player_.Move(sf::Vector2f(-1, 0), dt_game_, window.getSize());
			reimu_turn_ = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player_.Move(sf::Vector2f(1, 0), dt_game_, window.getSize());
			reimu_turn_ = 1;
		}
		else
		{
			player_.Idle(idle_fram_);
			reimu_turn_ = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && laser_cooldown_ > 0.1)
		{
			projectiles_.Spawn({ player_.Position().x, player_.Position().y - 50}, 0, -2000, 0);
			laser_cooldown_ = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			player_.SlowMove();
		}
		else
		{
			player_.NormalMove();
		}

		if (idle_cooldown_ > 0.1)
		{
			idle_fram_++;
			if (idle_fram_ > player_.IdleTextures().size()-1)
			{
				idle_fram_ = 0;
			}
			idle_cooldown_ = 0;
		}

		projectiles_.Refresh(dt_game_, window.getSize());


		window.draw(background_);
         		window.draw(background_move_1);
		window.draw(background_move_2);
		player_.Draw(window);
		window.draw(projectiles_);

		window.display();

		laser_cooldown_ += dt_game_;
		idle_cooldown_ += dt_game_;
		dt_game_ = clock.restart().asSeconds();
	}
}