#include <iostream>

#include "game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <windows.h>

constexpr float kCooldownLimit = 0.15f;

Game::Game() : background_(background_texture_), background_move_1_(background_move_texture_),
background_move_2_(background_move_texture_), score_(font_), game_over_(font_), player_hp_(font_)
{
	//HWND console_window = GetConsoleWindow();
	//ShowWindow(consoleWindow, SW_SHOW);
	//ShowWindow(consoleWindow, SW_HIDE);

	background_texture_.loadFromFile("assets/PNG/Background.png");
	background_move_texture_.loadFromFile("assets/PNG/Background_move.png");

	background_	= sf::Sprite(background_texture_);
	background_.setScale(sf::Vector2f(1.2f, 1.2f));
	background_move_1_ = sf::Sprite(background_move_texture_);
	background_move_1_.setScale(sf::Vector2f(1.2f, 1.2f));
	background_move_1_.setColor(sf::Color(255, 255, 255, 100));
	background_move_2_ = sf::Sprite(background_move_texture_);
	background_move_2_.setScale(sf::Vector2f(1.2f, 1.2f));
	background_move_2_.setColor(sf::Color(255, 255, 255, 100));


	window_.create(sf::VideoMode(sf::Vector2u(background_.getGlobalBounds().size.x, background_.getGlobalBounds().size.y)), "Space Shooter !!!");   // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-float-conversion, cppcoreguidelines-narrowing-conversions)

	starship_.SetPosition(sf::Vector2u(static_cast<float>(window_.getSize().x) / 2, static_cast<float>(window_.getSize().y / 6) * 5));  // NOLINT(bugprone-narrowing-conversions, bugprone-narrowing-conversions, bugprone-integer-division, clang-diagnostic-float-conversion, cppcoreguidelines-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

	background_move_2_.setPosition(sf::Vector2f(0, -static_cast<int>(window_.getSize().y)));  // NOLINT(clang-diagnostic-implicit-int-float-conversion)

	window_.setMouseCursorVisible(false);

	font_.openFromFile("assets/Font/Vermin Vibes 1989.ttf");
	score_.setFont(font_);
	game_over_.setFont(font_);
	player_hp_.setFont(font_);

	save_.Load(players_);

	music_background_.openFromFile("assets/Sound/Airwolf_2.wav");
	music_background_.setLooping(true);
	music_background_.play();
	music_background_.setVolume(15);

	music_game_over_.openFromFile("assets/Sound/Game Over.wav");
	music_game_over_.setVolume(25);
}
void Game::Loop()
{
	while (window_.isOpen())
	{
		if (!starship_.IsDead())
		{
			player_hp_.setString("HP : " + std::to_string(starship_.Hp()));
			player_hp_.setOrigin(sf::Vector2f(player_hp_.getGlobalBounds().size.x, 0));
			player_hp_.setPosition(sf::Vector2f(window_.getSize().x - 10, 5));  // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion)

			score_.setString("Score : " + std::to_string(score_numb_));
			score_.setOrigin(sf::Vector2f(0, player_hp_.getGlobalBounds().size.y));
			score_.setPosition(sf::Vector2f(5, window_.getSize().y - 15));  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)

			if (background_move_1_.getPosition().y >= window_.getSize().y)  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)
			{
				background_move_1_.setPosition(sf::Vector2f(0, -static_cast<int>(window_.getSize().y)));  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)
				background_move_2_.setPosition(sf::Vector2f(0, 0));
			}
			else if (background_move_2_.getPosition().y >= window_.getSize().y)  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)
			{
				background_move_2_.setPosition(sf::Vector2f(0, -static_cast<int>(window_.getSize().y)));  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)
				background_move_1_.setPosition(sf::Vector2f(0, 0));
			}

			background_move_1_.setPosition(sf::Vector2f(background_move_1_.getPosition().x, background_move_1_.getPosition().y + 0.2));  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-float-conversion, cppcoreguidelines-narrowing-conversions)
			background_move_2_.setPosition(sf::Vector2f(background_move_2_.getPosition().x, background_move_2_.getPosition().y + 0.2));  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-float-conversion, cppcoreguidelines-narrowing-conversions)



			if (isKeyPressed(sf::Keyboard::Key::Space))
			{

				player_missiles_.Spawn(starship_.GetPosition(), { 0, -1500 }, starship_.ShootSound(), 1);

			}
			if (isKeyPressed(sf::Keyboard::Key::Up))
				starship_.Move({ 0, -1 }, dt_, window_.getSize());
			if (isKeyPressed(sf::Keyboard::Key::Down))
				starship_.Move({ 0, 1 }, dt_, window_.getSize());
			if (isKeyPressed(sf::Keyboard::Key::Left) && isKeyPressed(sf::Keyboard::Key::Right))
			{
				starship_.Move({ 0, 0 }, dt_, window_.getSize());
				starship_.AnimUpdate(idle_frame_);
			}
			else if (isKeyPressed(sf::Keyboard::Key::Left))
				starship_.Move({ -1 , 0 }, dt_, window_.getSize());
			else if (isKeyPressed(sf::Keyboard::Key::Right))
				starship_.Move({ 1, 0 }, dt_, window_.getSize());
			else
			{
				starship_.Move({ 0, 0 }, dt_, window_.getSize());
				starship_.AnimUpdate(idle_frame_);
			}

			if (isKeyPressed(sf::Keyboard::Key::LShift))
				starship_.SlowMove();
			else
				starship_.NormalMove();


			if (idle_cooldown_ > 0.1)
			{
				idle_frame_++;
				if (idle_frame_ > starship_.IdleTextures().size() - 1)  // NOLINT(clang-diagnostic-sign-compare)
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

		while (const std::optional event = window_.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				players_.emplace_back(score_numb_);
				save_.SaveGame(players_);
				window_.close();
			}
		}


		if (isKeyPressed(sf::Keyboard::Key::Escape))
		{
			players_.emplace_back(score_numb_);
			save_.SaveGame(players_);
			window_.close();
		}

		window_.clear();
		window_.draw(background_);
		window_.draw(background_move_1_);
		window_.draw(background_move_2_);
		if (!starship_.IsDead())
		{
			window_.draw(player_missiles_);
			window_.draw(enemy_missiles_);
			window_.draw(asteroids_);
			window_.draw(enemy_manager_);
			window_.draw(starship_);
			window_.draw(player_hp_);
			window_.draw(score_);
			if (starship_.HeartIsVisible())
			{
				starship_.DrawHeart(window_);
			}
		}
		else
		{
			if (!players_.empty() && players_.at(0) > score_numb_)
			{
				game_over_.setString("Game Over \n Your Score : " + std::to_string(score_numb_) + "\n High Score : " + std::to_string(players_.at(0)));
			}
			else
			{
				game_over_.setString("Game Over \n Your Score : " + std::to_string(score_numb_) + "\n New High Score : " + std::to_string(score_numb_));
			}
			game_over_.setOrigin(sf::Vector2f(player_hp_.getGlobalBounds().size.x, player_hp_.getGlobalBounds().size.y));
			game_over_.setPosition(sf::Vector2f(window_.getSize().x / 2, window_.getSize().y / 2));  // NOLINT(bugprone-integer-division, bugprone-integer-division, clang-diagnostic-implicit-int-float-conversion, bugprone-narrowing-conversions, bugprone-narrowing-conversions)
			window_.draw(game_over_);

			music_background_.stop();

			if (music_game_over_.getStatus() == sf::Music::Status::Stopped)
			{
				music_game_over_.play();
			}

			if (music_game_over_.getStatus() == sf::Music::Status::Playing)
			{
				game_over_cooldown_ += dt_;
			}

			if (game_over_cooldown_ >= music_game_over_.getDuration().asSeconds())
			{
				players_.emplace_back(score_numb_);
				save_.SaveGame(players_);
				window_.close();
			}
		}
		window_.display();

		// At the end of the game loop
		idle_cooldown_ += dt_;
		hit_cooldown_ += dt_;
		dt_ = clock_.restart().asSeconds();
	}

	window_.setMouseCursorVisible(true);

}

