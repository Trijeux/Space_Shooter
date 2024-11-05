#include "Projectile.h"

#include <SFML/Graphics/RenderTarget.hpp>

int Projectile::counter_ = 0;
sf::Texture Projectile::texture_;

Projectile::Projectile()
{
	texture_.loadFromFile("Assets/Card.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(sprite_.getGlobalBounds().width / 2, 0);
	direction_ = { 0, -2000 };
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


