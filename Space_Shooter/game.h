#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "projectile_manager.h"


class Game
{
private:
	sf::RenderWindow window;
	ProjectileManager projectiles_;
	Player player;
	sf::Texture backgroud_texture_;
	sf::Texture backgroud_move_texture;
	sf::Sprite background_;
	sf::Sprite background_move_1;
	sf::Sprite background_move_2;


	sf::Clock clock;
	float dt_game_ = 0.0f;
	float laser_cooldown_ = 0;
	float idle_cooldown_ = 0;
	int idle_farm_ = 0;
	int reimu_turn_ = 0;
public:
	Game();
	void Loop();
};

#endif // GAME_H
