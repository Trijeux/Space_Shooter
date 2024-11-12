#include "entity.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


void Entity::Move(float dt, const sf::Vector2u& window_size)
{
	setPosition(getPosition() + direction_ * dt);

	hit_box_.left = getPosition().x;
	hit_box_.top = getPosition().y;

	sf::Vector2f position = getPosition();
	sf::Vector2f borders = sf::Vector2f(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2);

	if(position.x < -1 * borders.x || 
		position.x > window_size.x + borders.x || 
		position.y < -1 * borders.y || 
		position.y > window_size.y + borders.y)
	{
		is_dead_ = true;
	}

	// TODO : Tester les collisions avec des trucs ---
	
}

void Entity::SetPosition(float x, float y)
{
	setPosition(x, y);
}

void Entity::SetPosition(sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

bool Entity::Intersects(sf::FloatRect hitBox) const
{
	return hit_box_.intersects(hitBox);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	//// Draw the hitbox ---------------------------------------------------
	//sf::RectangleShape rectangle({ hit_box_.width, hit_box_.height });
	//rectangle.setPosition(hit_box_.left, hit_box_.top);

	//rectangle.setFillColor(sf::Color(255, 255, 255, 0));
	//rectangle.setOutlineColor(sf::Color(0, 0, 255, 255));
	//rectangle.setOutlineThickness(1);

	//target.draw(rectangle);

	target.draw(sprite_, states);
}
