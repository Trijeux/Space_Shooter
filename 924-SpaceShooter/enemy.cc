#include "enemy.h"

sf::Texture Enemy::texture_;
sf::SoundBuffer Enemy::sound_fx_card_;
sf::Sound Enemy::shoot_sound_ = sf::Sound(sound_fx_card_);


constexpr float kShootPeriod = 0.3f;
constexpr float kBurstPeriod = 0.5f;

Enemy::Enemy()
{

	texture_.loadFromFile("assets/PNG/Enemy.png");
	sprite_ = sf::Sprite(texture_);
	sprite_.setOrigin(sf::Vector2f(sprite_.getTextureRect().size.x / 2, sprite_.getTextureRect().size.y / 2));  // NOLINT(bugprone-integer-division, bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)

	hit_box_.size.x = static_cast<float>(sprite_.getTextureRect().size.x) * sprite_.getScale().x;
	hit_box_.size.y = static_cast<float>(sprite_.getTextureRect().size.y) * sprite_.getScale().y;

	direction_ = { 0, 150 };

	sound_fx_card_.loadFromFile("assets/Sound/Card.wav");
	shoot_sound_.setBuffer(sound_fx_card_);
	shoot_sound_.setVolume(15);
}

sf::Vector2f Enemy::GetPosition() const
{
	return getPosition();
}

void Enemy::Refresh(const float dt)
{
	shoot_dt_ += dt;

	burst_dt_ += dt;
	if(burst_dt_ >= kBurstPeriod)
	{
		wait_shoot_ = !wait_shoot_;
		burst_dt_ = 0;
	}
}

bool Enemy::Damage(const int damage)
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
