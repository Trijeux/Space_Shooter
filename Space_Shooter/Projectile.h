#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "entity.h"

class Projectile : public sf::Drawable, public sf::Transformable
{

private:
	static int counter_;
	static sf::Texture texture_;

	sf::Vector2f direction_;
	sf::Sprite sprite_;

	bool is_dead_ = false;

	sf::FloatRect hit_box_;

public:
	Projectile(float x, float y, float rotate);
	void Move(float dt, const sf::Vector2u& window_size);
	bool IsDead() const { return is_dead_; }

	void SetDeath() { is_dead_ = true; }

	sf::FloatRect HitBox() const { return hit_box_; }

	bool Intersects(const sf::FloatRect hit_box) const { return hit_box_.intersects(hit_box); }

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // PROJECTILE_H
