#ifndef STARSHIP_H
#define STARSHIP_H

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "asteroid.h"
#include "enemy.h"
#include "projectile.h"

constexpr float kSpeed = 500.f;

class Starship : public sf::Drawable, private sf::Transformable
{
private:
	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::FloatRect hit_box_;
	float speed_ = kSpeed;

	sf::Texture heart_visual_texture_;
	sf::Sprite heart_visual_sprite_;

	sf::Texture heart_hit_box_texture_;
	sf::Sprite heart_hit_box_sprite_;

	bool heart_is_visible_ = false;

	int hp_ = 10;

	bool is_dead_ = false;
public:

	int Hp() const { return hp_; }

	bool IsDead() const { return is_dead_; }

	bool HeartIsVisible_() { return heart_is_visible_; }
	Starship();
	void Move(sf::Vector2f direction, float dt, sf::Vector2u window_size);

	void SetPosition(sf::Vector2u position);
	sf::Vector2f GetPosition() { return getPosition(); }

	sf::FloatRect HitBox() { return hit_box_; }
	void CheckCollisions(std::vector<Asteroid>& asteroids);
	void CheckCollisions(std::vector<Projectile>& projectiles);
	void CheckCollisions(std::vector<Enemy>& enemies);

	void SlowMove();
	void NormalMove();
	void DrawHeart(sf::RenderWindow& window);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};

#endif
