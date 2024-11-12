#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "projectile_manager.h"
#include "starship.h"
#include "asteroid_manager.h"
#include "enemy.h"
#include "enemy_manager.h"
#include "save.h"

class Game
{

private:
	sf::RenderWindow window_;

	ProjectileManager player_missiles_;
	ProjectileManager enemy_missiles_;

	AsteroidManager asteroids_;
	EnemyManager enemy_manager_;

	Starship starship_;

	sf::Clock clock_;

	sf::Texture backgroud_texture_;
	sf::Texture backgroud_move_texture;
	sf::Sprite background_;
	sf::Sprite background_move_1;
	sf::Sprite background_move_2;

	sf::Font font_;
	sf::Text score_;
	sf::Text game_over_;
	sf::Text player_hp_;

	float dt_ = 0.016f;
	int score_numb_ = 0;
	int high_score_ = 0;

	std::vector<int> players_;

	Save save_;

public:
	Game();
	void Loop();
};


#endif // GAME_H
