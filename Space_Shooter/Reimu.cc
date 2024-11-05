#include "Reimu.h"


void Reimu::Turn(TurnFarm turn)
{
	reimu_sprite_.setTexture(turn_textures_.at(static_cast<int>(turn)));
}

void Reimu::Idle(int fram)
{
	reimu_sprite_.setTexture(idle_textures_.at(fram));
}

void Reimu::set_sprite()
{

	turn_textures_.at(static_cast<int>(TurnFarm::kRight)).loadFromFile("Assets/Reimu_right.png");
	turn_textures_.at(static_cast<int>(TurnFarm::kLeft)).loadFromFile("Assets/Reimu_left.png");

	heart_visual_texture_.loadFromFile("Assets/Heart.png");

	for (int idx = 0; idx < idle_textures_.size(); idx++)
	{
		idle_textures_.at(idx).loadFromFile("Assets/Reimu_Idle("+ std::to_string(idx) +").png");
	}

	heart_visual_sprite_.setTexture(heart_visual_texture_);
	heart_visual_sprite_.setOrigin(heart_visual_sprite_.getGlobalBounds().width / 2, heart_visual_sprite_.getGlobalBounds().height / 2);

	reimu_sprite_.setTexture(idle_textures_.at(0));

	reimu_sprite_.setOrigin(reimu_sprite_.getGlobalBounds().width / 2, reimu_sprite_.getGlobalBounds().height / 2);
	
}

void Reimu::draw_Reimu(sf::RenderWindow& window)
{
	window.draw(reimu_sprite_);
	if (heart_is_visible_)
		window.draw(heart_visual_sprite_);
}

void Reimu::set_position(sf::Vector2f pos)
{
	reimu_sprite_.setPosition(pos);
	heart_visual_sprite_.setPosition(reimu_sprite_.getPosition());
}

sf::Vector2f Reimu::get_position()
{
	return reimu_sprite_.getPosition();
}
