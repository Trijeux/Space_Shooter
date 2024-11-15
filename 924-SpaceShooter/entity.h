#ifndef ENTITY_H
#define ENTITY_H

#include <math.h>

#include <SFML/Graphics/Sprite.hpp>

class Entity : public sf::Drawable, protected sf::Transformable
{

	// Members -----------------
protected:
	sf::Vector2f direction_;
	sf::Sprite sprite_;
	sf::FloatRect hit_box_;

	bool is_dead_ = false;

	// Methods -----------------
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//Entity();
	sf::Sprite& Sprite() { return sprite_; }
	bool IsDead() const { return is_dead_; }
	virtual void SetDeath() { is_dead_ = true; }

	void Move(float dt, const sf::Vector2u& window_size);
	void SetPosition(float x, float y);
	void SetPosition(sf::Vector2f position);
	void SetScale(int scale_x, int scale_y);

	bool Intersects(sf::FloatRect hit_box) const;
	sf::FloatRect HitBox() const { return hit_box_; }

};

#endif // ENTITY_H
