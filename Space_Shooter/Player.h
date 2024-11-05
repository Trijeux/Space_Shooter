#ifndef PLAYER_H
#define PLAYER_H
#include "Projectile.h"
#include "Reimu.h"

class Player : public Reimu
{
private:
	const float max_speed_ = 600.0f;
	float speed_ = max_speed_;
public:
	Player();
	void MovePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size);

	void IdleAnimation(int);
	void SlowMove();
	void NormalMove();
};






#endif
