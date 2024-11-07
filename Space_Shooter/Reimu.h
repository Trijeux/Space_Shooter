#ifndef SHIP_H
#define SHIP_H
#include <array>

#include "SFML/Graphics.hpp"

class Reimu
{
private:
	enum class TurnFarm
	{
		kRight,
		kLeft,
	};


	const float max_speed_ = 600.0f;
	float speed_ = max_speed_;

	std::array<sf::Texture, 2> turn_textures_;
	std::array<sf::Texture, 4> idle_textures_;

	sf::Sprite reimu_sprite_;

	sf::Texture heart_visual_texture_;
	sf::Sprite heart_visual_sprite_;
public:
	Reimu();

	int hp_;
	bool heart_is_visible_ = false;

	void Turn(TurnFarm);
	void Idle(int);

	void SetSpritePlayer();

	void Draw(sf::RenderWindow& window) const;

	void SetPosition(sf::Vector2f pos);

	void Move(sf::Vector2f direction, float dt, const sf::Vector2u& window_size);

	void SlowMove();

	void NormalMove();

	auto Position() const { return reimu_sprite_.getPosition(); }

	auto IdleTextures() const { return idle_textures_; }
};

#endif


