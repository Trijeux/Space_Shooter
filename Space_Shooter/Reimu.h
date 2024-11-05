#ifndef SHIP_H
#define SHIP_H
#include <array>

#include "SFML/Graphics.hpp"

class Reimu
{
private:

protected:
	enum class TurnFarm
	{
		kRight,
		kLeft,
	};

	std::array<sf::Texture, 2> turn_textures_;
	std::array<sf::Texture, 4> idle_textures_;

	sf::Sprite reimu_sprite_;

	sf::Texture heart_visual_texture_;
	sf::Sprite heart_visual_sprite_;
public:
	int hp_;

	bool heart_is_visible_ = false;

	std::array<sf::Texture, 4> IdleTexture() const { return idle_textures_; }

	void Turn(TurnFarm);
	void Idle(int);

	void set_sprite();

	void draw_Reimu(sf::RenderWindow& window);

	void set_position(sf::Vector2f pos);
	sf::Vector2f get_position();

};

#endif


