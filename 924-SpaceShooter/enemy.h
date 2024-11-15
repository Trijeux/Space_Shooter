#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

#include "entity.h"

class Enemy : public Entity
{

private:
	static sf::Texture texture_;
	int hp_ = 3;

	float shoot_dt_ = 0.f;
	float burst_dt_ = 0.f;
	bool wait_shoot_ = false;

	void SetDeath();

	static sf::SoundBuffer soundFx_Card;
	static sf::Sound Shoot_Sound;
public:
	Enemy();

	sf::Sound& ShootSound() { return Shoot_Sound; }

	sf::Vector2f GetPosition();

	void Refresh(float dt);
	bool Damage(int damage);
	bool IsShootReady();

};

#endif // ENNEMY_H
