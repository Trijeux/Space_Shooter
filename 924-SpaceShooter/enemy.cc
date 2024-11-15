#include "enemy.h"

sf::Texture Enemy::texture_;
sf::SoundBuffer Enemy::soundFx_Card;
sf::Sound Enemy::Shoot_Sound;


constexpr float kShootPeriod = 0.3f;
constexpr float kBurstPeriod = 0.5f;

Enemy::Enemy()
{

	texture_.loadFromFile("assets\\PNG\\Enemy.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(sprite_.getTextureRect().width / 2, sprite_.getTextureRect().height / 2);

	hit_box_.width = (float)sprite_.getTextureRect().width * sprite_.getScale().x;
	hit_box_.height = (float)sprite_.getTextureRect().height * sprite_.getScale().y;

	direction_ = { 0, 150 };

	soundFx_Card.loadFromFile("assets/Sound/Card.wav");
	Shoot_Sound.setBuffer(soundFx_Card);
	Shoot_Sound.setVolume(15);
}

sf::Vector2f Enemy::GetPosition()
{
	return getPosition();
}

void Enemy::Refresh(float dt)
{
	shoot_dt_ += dt;

	burst_dt_ += dt;
	if(burst_dt_ >= kBurstPeriod)
	{
		wait_shoot_ = !wait_shoot_;
		burst_dt_ = 0;
	}
}

bool Enemy::Damage(int damage)
{
	hp_ -= damage;

	if (hp_ <= 0)
	{
		SetDeath();
		return true;
	}
	return false;
}

bool Enemy::IsShootReady()
{

	if (shoot_dt_ >= kShootPeriod && !wait_shoot_)
	{
		shoot_dt_ = 0;
		return true;
	}

	return false;

}


void Enemy::SetDeath()
{
	Entity::SetDeath();
}
