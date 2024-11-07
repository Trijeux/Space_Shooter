#include "reimu.h"

void Reimu::Move(sf::Vector2f direction, float dt, const sf::Vector2u& window_size)
{
	sf::Vector2f new_pos = reimu_sprite_.getPosition() + speed_ * direction * dt;

	if (reimu_sprite_.getPosition().x > new_pos.x)
	{
		reimu_sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kLeft)));
	}
	else if (reimu_sprite_.getPosition().x < new_pos.x)
	{
		reimu_sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kRight)));
	}

	if (!(new_pos.x < 0 + reimu_sprite_.getGlobalBounds().width / 2 || new_pos.x > window_size.x - reimu_sprite_.getGlobalBounds().width / 2 || new_pos.y < 0 + reimu_sprite_.getGlobalBounds().height / 2 || new_pos.y > window_size.y - reimu_sprite_.getGlobalBounds().height / 2))
	{
		SetPosition(new_pos);
	}

}

void Reimu::SlowMove()
{
	speed_ = max_speed_ / 2;
	heart_is_visible_ = true;
}

void Reimu::NormalMove()
{
	speed_ = max_speed_;
	heart_is_visible_ = false;
}


Reimu::Reimu()
{
	SetSpritePlayer();
}

void Reimu::Turn(TurnFarm turn)
{
	reimu_sprite_.setTexture(turn_textures_.at(static_cast<int>(turn)));
}

void Reimu::Idle(int fram)
{
	reimu_sprite_.setTexture(idle_textures_.at(fram));
}

void Reimu::SetSpritePlayer()
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

void Reimu::Draw(sf::RenderWindow& window) const
{
	window.draw(reimu_sprite_);
	if (heart_is_visible_)
		window.draw(heart_visual_sprite_);
}

void Reimu::SetPosition(sf::Vector2f pos)
{
	reimu_sprite_.setPosition(pos);
	heart_visual_sprite_.setPosition(reimu_sprite_.getPosition());
}