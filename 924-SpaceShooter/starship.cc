#include "starship.h"

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

void Starship::AnimUpdate(int fram)
{
	sprite_.setTexture(idle_textures_.at(fram));
}

void Starship::HitAnimation(float& hit_cooldown_)
{
	if (hit_cooldown_ > 0.1f && hit_cooldown_ < 0.12f)
	{
		sprite_.setColor(sf::Color(255, 255, 255, 50));
	}
	else if (hit_cooldown_ > 0.2f)
	{
		sprite_.setColor(sf::Color(255, 255, 255, 255));
		hit_cooldown_ = 0;
		num_hit_anim++;
	}

	if (num_hit_anim >= 6)
	{
		num_hit_anim = 0;
		is_hit_ = false;
	}
}

Starship::Starship()
{
	turn_textures_.at(static_cast<int>(TurnFarm::kRight)).loadFromFile("Assets\\PNG\\Reimu_right.png");
	turn_textures_.at(static_cast<int>(TurnFarm::kLeft)).loadFromFile("Assets\\PNG\\Reimu_left.png");

	for (int idx = 0; idx < idle_textures_.size(); idx++)
	{
		idle_textures_.at(idx).loadFromFile("Assets\\PNG\\Reimu_Idle(" + std::to_string(idx) + ").png");
	}

	sprite_.setTexture(idle_textures_.at(0));
	sprite_.setOrigin(idle_textures_.at(0).getSize().x / 2, idle_textures_.at(0).getSize().y / 2);

	heart_visual_texture_.loadFromFile("assets\\PNG\\Heart.png");
	heart_visual_sprite_.setTexture(heart_visual_texture_);
	heart_visual_sprite_.setOrigin(heart_visual_sprite_.getGlobalBounds().width / 2, heart_visual_sprite_.getGlobalBounds().height / 2);

	heart_hit_box_texture_.loadFromFile("assets\\PNG\\Heart_Gameplay.png");
	heart_hit_box_sprite_.setTexture(heart_hit_box_texture_);
	heart_hit_box_sprite_.setOrigin(heart_hit_box_sprite_.getGlobalBounds().width / 2, heart_hit_box_sprite_.getGlobalBounds().height / 2);


	hit_box_.height = (float)heart_hit_box_sprite_.getTextureRect().width;
	hit_box_.width = (float)heart_hit_box_sprite_.getTextureRect().height;

	soundFx_Card.loadFromFile("assets/Sound/Card.wav");
	Shoot_Sound.setBuffer(soundFx_Card);
	Shoot_Sound.setVolume(30);

	soundFx_Hit.loadFromFile("assets/Sound/damage.wav");
	Hit_Sound.setBuffer(soundFx_Hit);
	Hit_Sound.setVolume(50);
}

void Starship::Move(sf::Vector2f direction, float dt, sf::Vector2u window_size)
{
	sf::Vector2f new_pos = getPosition() + speed_ * direction * dt;

	if (getPosition().x > new_pos.x)
	{
		sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kLeft)));
	}
	else if (getPosition().x < new_pos.x)
	{
		sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kRight)));
	}

	if (!(new_pos.x < 0 + sprite_.getGlobalBounds().width / 2 || new_pos.x > window_size.x - sprite_.getGlobalBounds().width / 2 || new_pos.y < 0 + sprite_.getGlobalBounds().height / 2 || new_pos.y > window_size.y - sprite_.getGlobalBounds().height / 2))
	{
		move(direction * speed_ * dt);
		heart_visual_sprite_.setPosition(getPosition());
		heart_hit_box_sprite_.setPosition(getPosition());
	}
	
	hit_box_.left = getPosition().x - hit_box_.width / 2;
	hit_box_.top = getPosition().y - hit_box_.height / 2;
}

void Starship::SetPosition(sf::Vector2u position)
{
	setPosition(sf::Vector2f(position));
	hit_box_.left = getPosition().x - hit_box_.width / 2;
	hit_box_.top = getPosition().y - hit_box_.height / 2;
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
	Hit_Sound.play();
}

void Starship::CheckCollisions(std::vector<Asteroid>& asteroids)
{
	for (auto& a : asteroids)
	{
		if (a.IsDead() == false && hit_box_.intersects(a.HitBox()))
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
		if (p.IsDead() == false && hit_box_.intersects(p.HitBox()))
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
		if (e.IsDead() == false && hit_box_.intersects(e.HitBox()))
		{
			e.Damage(5);
			HitStarShip();
		}
	}
}

void Starship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	// Draw the hitbox
	//sf::RectangleShape rectangle({hit_box_.width, hit_box_.height});
	//rectangle.setPosition(hit_box_.left, hit_box_.top);
	//rectangle.setFillColor(sf::Color(255,255,255,0));
	//rectangle.setOutlineColor(sf::Color(255,0,0,255));
	//rectangle.setOutlineThickness(1);

	//target.draw(rectangle);

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

void Starship::DrawHeart(sf::RenderWindow& window)
{
	window.draw(heart_visual_sprite_);
}
