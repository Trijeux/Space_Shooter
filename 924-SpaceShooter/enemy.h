#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

#include "entity.h"

class Enemy final : public Entity
{

private:
	static sf::Texture texture_;
	int hp_ = 3;

	float shoot_dt_ = 0.f;
	float burst_dt_ = 0.f;
	bool wait_shoot_ = false;

	void SetDeath() override;

	static sf::SoundBuffer sound_fx_card_;
	static sf::Sound shoot_sound_;
public:
	Enemy();

	static sf::Sound& ShootSound() { return shoot_sound_; }

	sf::Vector2f GetPosition() const;

	void Refresh(float dt);
	bool Damage(int damage);
	bool IsShootReady();

};

#endif // ENEMY_H
