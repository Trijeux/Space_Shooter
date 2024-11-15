#include "projectile.h"

#include <array>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

sf::Texture Projectile::texture_;

Projectile::Projectile(const sf::Vector2f direction)
{
	texture_.loadFromFile("assets\\PNG\\Card.png");

	sprite_.setTexture(texture_);
	sprite_.setColor(sf::Color(255, 255, 255, 255));
	//setOrigin(0, texture_.getSize().y / 2);


	// Inversion width / height because of rotation
	hit_box_.height = static_cast<float>(sprite_.getTextureRect().width) * getScale().x;
	hit_box_.width = static_cast<float>(sprite_.getTextureRect().height) * getScale().y;

	direction_ = direction;

}



