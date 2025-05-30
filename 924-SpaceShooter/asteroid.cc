#include "asteroid.h"

#include <random>
#include <SFML/Graphics/Texture.hpp>

sf::Texture Asteroid::texture_;

Asteroid::Asteroid()
{

	texture_.loadFromFile("assets/PNG/YingYang.png");
	sprite_ = sf::Sprite(texture_);
	//sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);

	hit_box_.size.x = static_cast<float>(sprite_.getTextureRect().size.x) * getScale().x;
	hit_box_.size.y = static_cast<float>(sprite_.getTextureRect().size.y) * getScale().y;

	// Seed with a real random value, if available
	std::random_device rn_device;
	// Choose a random mean between 1 and 6
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> rnd_x( -50,50);
	std::uniform_real_distribution<float> rnd_y(150.0, 250.0);


	direction_ = { rnd_x(engine) , rnd_y(engine) };

}
