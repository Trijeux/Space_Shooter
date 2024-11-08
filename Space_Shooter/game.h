#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "projectile_manager.h"
#include "reimu.h"

class Game
{
private:
	sf::RenderWindow window;
	Reimu player_;
	ProjectileManager projectiles_;
	sf::Texture backgroud_texture_;
	sf::Texture backgroud_move_texture;
	sf::Sprite background_;
	sf::Sprite background_move_1;
	sf::Sprite background_move_2;


	sf::Clock clock;
	float dt_game_ = 0.0f;
	float laser_cooldown_ = 0;
	float idle_cooldown_ = 0;
	int idle_fram_ = 0;
	int reimu_turn_ = 0;
public:
	Game();
	void Loop();
};

#endif // GAME_H
