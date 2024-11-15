#ifndef STARSHIP_H
#define STARSHIP_H

#include <array>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Audio.hpp>

#include "asteroid.h"
#include "enemy.h"
#include "projectile.h"

constexpr float kSpeed = 500.f;

class Starship final : public sf::Drawable, private sf::Transformable
{
private:
	enum class TurnFarm
	{
		kRight,
		kLeft,
	};


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

	std::array<sf::Texture, 2> turn_textures_;
	std::array<sf::Texture, 4> idle_textures_;

	bool is_hit_ = false;
	int num_hit_anim_ = 0;

	sf::SoundBuffer sound_fx_card_;
	sf::Sound shoot_sound_;

	sf::SoundBuffer sound_fx_hit_;
	sf::Sound hit_sound_;
public:
	sf::Sound& ShootSound() { return shoot_sound_; }

	void AnimUpdate(int fram);

	void HitAnimation(float& hit_cooldown);

	bool IsHit() const { return is_hit_; }

	std::array<sf::Texture, 4> IdleTextures() { return idle_textures_; }

	int Hp() const { return hp_; }

	bool IsDead() const { return is_dead_; }

	bool HeartIsVisible() const { return heart_is_visible_; }
	Starship();
	void Move(sf::Vector2f direction, float dt, sf::Vector2u window_size);

	void SetPosition(sf::Vector2u position);
	void HitStarShip();
	sf::Vector2f GetPosition() const { return getPosition(); }

	sf::FloatRect HitBox() const { return hit_box_; }
	void CheckCollisions(std::vector<Asteroid>& asteroids);
	void CheckCollisions(std::vector<Projectile>& projectiles);
	void CheckCollisions(std::vector<Enemy>& enemies);

	void SlowMove();
	void NormalMove();
	void DrawHeart(sf::RenderWindow& window) const;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
};

#endif
