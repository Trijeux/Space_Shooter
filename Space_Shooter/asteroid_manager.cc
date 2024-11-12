#include "asteroid_manager.h"

#include <random>

void AsteroidManager::Refresh(float dt, const sf::Vector2u& window_size)
{

	time_elapsed_ += dt;
	if(time_elapsed_ > 1.f)
	{
		asteroids_.emplace_back();

		// Tirage aléatoire de Y
		// // Seed with a real random value, if available
		std::random_device rn_device;
		// Choose a random mean between 1 and 6
		std::default_random_engine engine(rn_device());
		std::uniform_real_distribution<float> uniform_dist(0, window_size.x);

		asteroids_.back().SetPosition(uniform_dist(engine), 0);

		time_elapsed_ = 0;
	}

	// Cleaning unused projectiles
	auto removed_elt = std::remove_if(
		asteroids_.begin(),
		asteroids_.end(),
		[](const Asteroid& p) {return p.IsDead(); }
	);

	if (removed_elt != asteroids_.end())
	{
		asteroids_.erase(removed_elt);
	}

	// Move remaining projectiles
	for (Asteroid& p : asteroids_)
	{
		p.Move(dt, window_size);
	}
}

void AsteroidManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& myAsteroid : asteroids_)
	{
		target.draw(myAsteroid);
	}
}

