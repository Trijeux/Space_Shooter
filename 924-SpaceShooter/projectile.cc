#include "projectile.h"

#include <array>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

sf::Texture Projectile::texture_;

Projectile::Projectile(const sf::Vector2f direction)
{
	texture_.loadFromFile("assets\\PNG\\Card.png");

	sprite_ = sf::Sprite(texture_);
	sprite_.setColor(sf::Color(255, 255, 255, 255));
	//setOrigin(0, texture_.getSize().y / 2);


	// Inversion width / height because of rotation
	hit_box_.size.y = static_cast<float>(sprite_.getTextureRect().size.x) * getScale().x;
	hit_box_.size.x = static_cast<float>(sprite_.getTextureRect().size.y) * getScale().y;

	direction_ = direction;

}



