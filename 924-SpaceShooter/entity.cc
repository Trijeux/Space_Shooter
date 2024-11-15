#include "entity.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


void Entity::Move(const float dt, const sf::Vector2u& window_size)
{
	setPosition(getPosition() + direction_ * dt);

	hit_box_.left = getPosition().x;
	hit_box_.top = getPosition().y;

	const sf::Vector2f position = getPosition();

	if(const auto borders = sf::Vector2f(sprite_.getGlobalBounds().width / 2, sprite_.getGlobalBounds().height / 2); position.x < -1 * borders.x || 
		position.x > window_size.x + borders.x ||   // NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion)
		position.y < -1 * borders.y || 
		position.y > window_size.y + borders.y)		// NOLINT(bugprone-narrowing-conversions, cppcoreguidelines-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion)
	{
		is_dead_ = true;
	}
}

void Entity::SetPosition(const float x, const float y)
{
	setPosition(x, y);
}

void Entity::SetPosition(const sf::Vector2f position)
{
	setPosition(position.x, position.y);
}

void Entity::SetScale(const int scale_x, const int scale_y)
{
	setScale(scale_x, scale_y);  // NOLINT(bugprone-narrowing-conversions, bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)
}

bool Entity::Intersects(const sf::FloatRect hit_box) const
{
	return hit_box_.intersects(hit_box);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(sprite_, states);
}
