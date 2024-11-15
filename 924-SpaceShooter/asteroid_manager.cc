#include "asteroid_manager.h"

#include <random>

void AsteroidManager::Refresh(const float dt, const sf::Vector2u& window_size)
{

	time_elapsed_ += dt;
	if (time_elapsed_ > 0.65f)
	{
		asteroids_.emplace_back();

		// Tirage aléatoire de Y  // NOLINT(clang-diagnostic-invalid-utf8)
		// // Seed with a real random value, if available
		std::random_device rn_device;
		// Choose a random mean between 1 and 6
		std::default_random_engine engine(rn_device());
		std::uniform_real_distribution<float> uniform_dist(0, window_size.y);  // NOLINT(bugprone-narrowing-conversions, clang-diagnostic-implicit-int-float-conversion, cppcoreguidelines-narrowing-conversions)

		asteroids_.back().SetPosition(uniform_dist(engine), 0);

		time_elapsed_ = 0;
	}

	// Cleaning unused projectiles

	if (const auto removed_elt = std::ranges::remove_if(asteroids_,[](const Asteroid& p) {return p.IsDead(); }).begin(); removed_elt != asteroids_.end())
	{
		asteroids_.erase(removed_elt);
	}

	// Move remaining projectiles
	for (Asteroid& p : asteroids_)
	{
		p.Move(dt, window_size);
		/*rotation_ += rotation_fram_
		if (rotation_ >= 360)
		{
			rotation_ = 0;
		}
		p.Sprite().setRotation(rotation_);*/
	}
}

void AsteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& my_asteroid : asteroids_)
	{
		target.draw(my_asteroid);
	}
}

