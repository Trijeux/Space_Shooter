#include "Player.h"

#include <iostream>

Player::Player()
{
	set_sprite();
}

void Player::MovePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size)
{
	sf::Vector2f new_pos = get_position() + speed_ * direction * dt;

	if (reimu_sprite_.getPosition().x > new_pos.x)
	{
		reimu_sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kLeft)));
	}
	else if (reimu_sprite_.getPosition().x < new_pos.x)
	{
		reimu_sprite_.setTexture(turn_textures_.at(static_cast<int>(TurnFarm::kRight)));
	}

	if (!(new_pos.x < 0 + reimu_sprite_.getGlobalBounds().width/2 || new_pos.x > window_size.x - reimu_sprite_.getGlobalBounds().width / 2 || new_pos.y < 0 + reimu_sprite_.getGlobalBounds().height / 2 || new_pos.y > window_size.y - reimu_sprite_.getGlobalBounds().height / 2))
	{
		set_position(new_pos);
	}

}

void Player::IdleAnimation(int fram)
{
	Idle(fram);
}

void Player::SlowMove()
{
	speed_ = max_speed_ / 2;
	heart_is_visible_ = true;
}

void Player::NormalMove()
{
	speed_ = max_speed_;
	heart_is_visible_ = false;
}

