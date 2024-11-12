#include "projectile.h"

#include <SFML/Graphics/RenderTarget.hpp>

int Projectile::counter_ = 0;
sf::Texture Projectile::texture_;

Projectile::Projectile(float x, float y, const float rotate)
{
	texture_.loadFromFile("Assets/Card.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, 0);
	sprite_.setRotation(rotate);
	sprite_.setColor(sf::Color(255, 255, 255, 150));
	direction_ = { x, y };
	hit_box_.height = (float)sprite_.getTextureRect().width * sprite_.getScale().x;
	hit_box_.width = (float)sprite_.getTextureRect().height * sprite_.getScale().y;
	counter_++;
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
    	target.draw(sprite_, states);
}

void Projectile::Move(float dt, const sf::Vector2u& window_size)
{
	setPosition(getPosition() + direction_* dt);

	sf::Vector2f pos = getPosition();

	if (pos.x < 0 || pos.x > window_size.x || pos.y < 0 || pos.y > window_size.y)
	{
		is_dead_ = true;
	}
}


