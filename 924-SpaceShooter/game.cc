#include <iostream>

#include "game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <windows.h>

constexpr float kCooldownLimit = 0.15f;

Game::Game()
{
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_HIDE);

	backgroud_texture_.loadFromFile("assets/PNG/Background.png");
	backgroud_move_texture.loadFromFile("assets/PNG/Background_move.png");

	background_.setTexture(backgroud_texture_);
	background_.setScale(1.2f, 1.2f);
	background_move_1.setTexture(backgroud_move_texture);
	background_move_1.setScale(1.2f, 1.2f);
	background_move_1.setColor(sf::Color(255, 255, 255, 100));
	background_move_2.setTexture(backgroud_move_texture);
	background_move_2.setScale(1.2f, 1.2f);
	background_move_2.setColor(sf::Color(255, 255, 255, 100));


	window_.create(sf::VideoMode(background_.getGlobalBounds().width, background_.getGlobalBounds().height), "Space Shooter !!!");

	starship_.SetPosition(sf::Vector2u(static_cast<float>(window_.getSize().x) / 2, static_cast<float>(window_.getSize().y / 6) * 5));

	background_move_2.setPosition(0, -static_cast<int>(window_.getSize().y));

	window_.setMouseCursorVisible(false);

	font_.loadFromFile("assets/Font/Vermin Vibes 1989.ttf");
	score_.setFont(font_);
	game_over_.setFont(font_);
	player_hp_.setFont(font_);

	save_.Load(players_);

	music_.openFromFile("assets/Sound/Airwolf_2.wav");
	music_.setLoop(true);
	music_.play();
	music_.setVolume(15);
}
void Game::Loop()
{
	while (window_.isOpen())
	{
		if (!starship_.IsDead())
		{
			player_hp_.setString("HP : " + std::to_string(starship_.Hp()));
			player_hp_.setOrigin(player_hp_.getGlobalBounds().width, 0);
			player_hp_.setPosition(window_.getSize().x - 10, 5);

			score_.setString("Score : " + std::to_string(score_numb_));
			score_.setOrigin(0, player_hp_.getGlobalBounds().height);
			score_.setPosition(5, window_.getSize().y - 15);

			if (background_move_1.getPosition().y >= window_.getSize().y)
			{
				background_move_1.setPosition(0, -static_cast<int>(window_.getSize().y));
				background_move_2.setPosition(0, 0);
			}
			else if (background_move_2.getPosition().y >= window_.getSize().y)
			{
				background_move_2.setPosition(0, -static_cast<int>(window_.getSize().y));
				background_move_1.setPosition(0, 0);
			}

			background_move_1.setPosition(background_move_1.getPosition().x, background_move_1.getPosition().y + 0.2);
			background_move_2.setPosition(background_move_2.getPosition().x, background_move_2.getPosition().y + 0.2);



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				player_missiles_.Spawn(starship_.GetPosition(), { 0, -1500 }, starship_.ShootSound());
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				starship_.Move({ 0, -1 }, dt_, window_.getSize());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				starship_.Move({ 0, 1 }, dt_, window_.getSize());
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				starship_.Move({ 0, 0 }, dt_, window_.getSize());
				starship_.AnimUpdate(idle_frame_);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				starship_.Move({ -1 , 0 }, dt_, window_.getSize());
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				starship_.Move({ 1, 0 }, dt_, window_.getSize());
			else
			{
				starship_.Move({ 0, 0 }, dt_, window_.getSize());
				starship_.AnimUpdate(idle_frame_);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				starship_.SlowMove();
			else
				starship_.NormalMove();


			if (idle_cooldown_ > 0.1)
			{
				idle_frame_++;
				if (idle_frame_ > starship_.IdleTextures().size() - 1)
				{
					idle_frame_ = 0;
				}
				idle_cooldown_ = 0;
			}

			player_missiles_.Refresh(dt_, window_.getSize());
			asteroids_.Refresh(dt_, window_.getSize());

			enemy_missiles_.Refresh(dt_, window_.getSize());
			enemy_manager_.Refresh(dt_, window_.getSize(), enemy_missiles_);

			if (!starship_.IsHit())
			{
				starship_.CheckCollisions(asteroids_.GetEntities());
				starship_.CheckCollisions(enemy_manager_.GetEntities());
				starship_.CheckCollisions(enemy_missiles_.GetEntities());
			}
			else
			{
				starship_.HitAnimation(hit_cooldown_);
			}


			if (player_missiles_.CheckCollisions(asteroids_.GetEntities()))
				score_numb_ += 50;

			if (player_missiles_.CheckCollisions(enemy_manager_.GetEntities()))
				score_numb_ += 100;

		}

		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				players_.emplace_back(score_numb_);
				save_.SaveGame(players_);
				window_.close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			players_.emplace_back(score_numb_);
			save_.SaveGame(players_);
			window_.close();
		}

		window_.clear();
		window_.draw(background_);
		window_.draw(background_move_1);
		window_.draw(background_move_2);
		if (!starship_.IsDead())
		{
			window_.draw(player_missiles_);
			window_.draw(enemy_missiles_);
			window_.draw(asteroids_);
			window_.draw(enemy_manager_);
			window_.draw(starship_);
			window_.draw(player_hp_);
			window_.draw(score_);
			if (starship_.HeartIsVisible_())
			{
				starship_.DrawHeart(window_);
			}
		}
		else
		{
			if (players_.size() > 0 && players_.at(0) > score_numb_)
			{
				game_over_.setString("Game Over \n Your Score : " + std::to_string(score_numb_) + "\n High Score : " + std::to_string(players_.at(0)));
			}
			else
			{
				game_over_.setString("Game Over \n Your Score : " + std::to_string(score_numb_) + "\n New High Score : " + std::to_string(score_numb_));
			}
			game_over_.setOrigin(player_hp_.getGlobalBounds().width, player_hp_.getGlobalBounds().height);
			game_over_.setPosition(window_.getSize().x / 2, window_.getSize().y / 2);
			window_.draw(game_over_);
		}
		window_.display();

		// At the end of the game loop
		idle_cooldown_ += dt_;
		hit_cooldown_ += dt_;
		dt_ = clock_.restart().asSeconds();
	}

	window_.setMouseCursorVisible(true);

}

