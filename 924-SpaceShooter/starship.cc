#include "starship.h"

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

void Starship::AnimUpdate(const int fram)
{
	sprite_.setTexture(idle_textures_.at(fram));
}

void Starship::HitAnimation(float& hit_cooldown)
{
	if (hit_cooldown > 0.1f && hit_cooldown < 0.12f)
	{
		sprite_.setColor(sf::Color(255, 255, 255, 50));
	}
	else if (hit_cooldown > 0.2f)
	{
		sprite_.setColor(sf::Color(255, 255, 255, 255));
		hit_cooldown = 0;
		num_hit_anim_++;
	}

	if (num_hit_anim_ >= 6)
	{
		num_hit_anim_ = 0;
		is_hit_ = false;
	}
}

Starship::Starship() : sprite_(empty_texture_), heart_visual_sprite_(heart_visual_texture_), heart_hit_box_sprite_(heart_hit_box_texture_),
shoot_sound_(sound_fx_card_), hit_sound_(sound_fx_hit_)
{
	turn_textures_.at(static_cast<int>(TurnFarm::kRight)).loadFromFile("Assets/PNG/Reimu_right.png");
	turn_textures_.at(static_cast<int>(TurnFarm::kLeft)).loadFromFile("Assets/PNG/Reimu_left.png");

	for (int idx = 0; idx < idle_textures_.size(); idx++)
	{
		idle_textures_.at(idx).loadFromFile("Assets/PNG/Reimu_Idle(" + std::to_string(idx) + ").png");
	}

	sprite_ = sf::Sprite(idle_textures_.at(0));
	sprite_.setOrigin(sf::Vector2f(idle_textures_.at(0).getSize().x / 2, idle_textures_.at(0).getSize().y / 2));  // NOLINT(bugprone-integer-division, clang-diagnostic-implicit-int-float-conversion, bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions)

	heart_visual_texture_.loadFromFile("assets/PNG/Heart.png");
	heart_visual_sprite_ = sf::Sprite(heart_visual_texture_);
	heart_visual_sprite_.setOrigin(sf::Vector2f(heart_visual_sprite_.getGlobalBounds().size.x / 2, heart_visual_sprite_.getGlobalBounds().size.y / 2));

	heart_hit_box_texture_.loadFromFile("assets/PNG/Heart_Gameplay.png");
	heart_hit_box_sprite_ = sf::Sprite(heart_hit_box_texture_);
	heart_hit_box_sprite_.setOrigin(sf::Vector2f(heart_hit_box_sprite_.getGlobalBounds().size.x / 2, heart_hit_box_sprite_.getGlobalBounds().size.y / 2));


	hit_box_.size.y = static_cast<float>(heart_hit_box_sprite_.getTextureRect().size.x);
	hit_box_.size.x = static_cast<float>(heart_hit_box_sprite_.getTextureRect().size.y);

	sound_fx_card_.loadFromFile("assets/Sound/Card.wav");
	shoot_sound_.setBuffer(sound_fx_card_);
	shoot_sound_.setVolume(30);

	sound_fx_hit_.loadFromFile("assets/Sound/damage.wav");
	hit_sound_.setBuffer(sound_fx_hit_);
	hit_sound_.setVolume(50);
}

void Starship::Move(const sf::Vector2f direction, const float dt, const sf::Vector2u window_size)
{
	const sf::Vector2f new_pos = getPosition() + speed_ * direction * dt;

	if (getPosition().x > new_pos.x)
	{
		sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kLeft)));
	}
	else if (getPosition().x < new_pos.x)
	{
		sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kRight)));
	}

	if (!(new_pos.x < 0 + sprite_.getGlobalBounds().size.x / 2 || new_pos.x > window_size.x - sprite_.getGlobalBounds().size.y / 2 || new_pos.y < 0 + sprite_.getGlobalBounds().size.y / 2 || new_pos.y > window_size.y - sprite_.getGlobalBounds().size.y / 2))  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)
	{
		move(direction * speed_ * dt);
		heart_visual_sprite_.setPosition(getPosition());
		heart_hit_box_sprite_.setPosition(getPosition());
	}
	
	hit_box_.position.x = getPosition().x - hit_box_.size.x / 2;
	hit_box_.position.y = getPosition().y - hit_box_.size.y / 2;
}

void Starship::SetPosition(const sf::Vector2u position)
{
	setPosition(sf::Vector2f(position));
	hit_box_.position.x = getPosition().x - hit_box_.size.x / 2;
	hit_box_.position.y = getPosition().y - hit_box_.size.y / 2;
	heart_visual_sprite_.setPosition(getPosition());
	heart_hit_box_sprite_.setPosition(getPosition());
}

void Starship::HitStarShip()
{
	hp_--;
	if (hp_ <= 0)
	{
		is_dead_ = true;
	}
	is_hit_ = true;
	hit_sound_.play();
}

void Starship::CheckCollisions(std::vector<Asteroid>& asteroids)
{
	for (auto& a : asteroids)
	{
		if (a.IsDead() == false && hit_box_.findIntersection(a.HitBox()))
		{
			a.SetDeath();
			HitStarShip();
		}
	}
}

void Starship::CheckCollisions(std::vector<Projectile>& projectiles)
{
	for (auto& p : projectiles)
	{
		if (p.IsDead() == false && hit_box_.findIntersection(p.HitBox()))
		{
			p.SetDeath();
			HitStarShip();
		}
	}
}

void Starship::CheckCollisions(std::vector<Enemy>& enemies)
{
	for (auto& e : enemies)
	{
		if (e.IsDead() == false && hit_box_.findIntersection(e.HitBox()))
		{
			e.Damage(5);
			HitStarShip();
		}
	}
}

void Starship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite_, states);
}

void Starship::SlowMove()
{
	speed_ = kSpeed / 2;
	heart_is_visible_ = true;
}

void Starship::NormalMove()
{
	speed_ = kSpeed;
	heart_is_visible_ = false;
}

void Starship::DrawHeart(sf::RenderWindow& window) const
{
	window.draw(heart_visual_sprite_);
}
