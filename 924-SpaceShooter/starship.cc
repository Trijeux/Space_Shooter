#include "starship.h"

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

Starship::Starship()
{
	texture_.loadFromFile("assets\\PNG\\Reimu_Idle(0).png");

	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);

	heart_visual_texture_.loadFromFile("assets\\PNG\\Heart.png");
	heart_visual_sprite_.setTexture(heart_visual_texture_);
	heart_visual_sprite_.setOrigin(heart_visual_sprite_.getGlobalBounds().width / 2, heart_visual_sprite_.getGlobalBounds().height / 2);

	heart_hit_box_texture_.loadFromFile("assets\\PNG\\Heart_Gameplay.png");
	heart_hit_box_sprite_.setTexture(heart_hit_box_texture_);
	heart_hit_box_sprite_.setOrigin(heart_hit_box_sprite_.getGlobalBounds().width / 2, heart_hit_box_sprite_.getGlobalBounds().height / 2);


	hit_box_.height = (float)heart_hit_box_sprite_.getTextureRect().width;
	hit_box_.width = (float)heart_hit_box_sprite_.getTextureRect().height;
}

void Starship::Move(sf::Vector2f direction, float dt, sf::Vector2u window_size)
{
	sf::Vector2f new_pos = getPosition() + speed_ * direction * dt;

	if (getPosition().x > new_pos.x)
	{
		//sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kLeft)));
	}
	else if (getPosition().x < new_pos.x)
	{
		//sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kRight)));
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

void Starship::CheckCollisions(std::vector<Asteroid>& asteroids)
{
	for (auto& a : asteroids)
	{
		if (a.IsDead() == false && hit_box_.intersects(a.HitBox()))
		{
			a.SetDeath();
			hp_--;
			if (hp_ <= 0)
			{
				is_dead_ = true;
			}
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
			hp_--;
			if (hp_ <= 0)
			{
				is_dead_ = true;
			}
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
			// Starship damages ?????
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
