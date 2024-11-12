#include "enemy_manager.h"

#include <random>
#include <SFML/Graphics/RenderTarget.hpp>

#include "projectile.h"

constexpr float kSpawnPeriod = 0.95f;

void EnemyManager::Refresh(float dt, const sf::Vector2u& window_size, ProjectileManager& enemy_missiles_manager)
{

	spawn_dt_ += dt;
	if (spawn_dt_ > kSpawnPeriod)
	{
		enemies_.emplace_back();

		// Tirage aléatoire de Y
		// // Seed with a real random value, if available
		std::random_device rn_device;
		// Choose a random mean between 1 and 6
		std::default_random_engine engine(rn_device());
		std::uniform_real_distribution<float> uniform_dist(0, window_size.y);

		enemies_.back().SetPosition(uniform_dist(engine), 0);

		spawn_dt_ = 0;
	}

	// Cleaning unused projectiles
	auto removed_elt = std::remove_if(
		enemies_.begin(),
		enemies_.end(),
		[](const Enemy& e) {return e.IsDead(); }
	);

	if (removed_elt != enemies_.end())
	{
		enemies_.erase(removed_elt);
	}

	// Move remaining projectiles
	for (auto& e : enemies_)
	{
		e.Move(dt, window_size);
		e.Refresh(dt);
		if (e.IsShootReady())
		{
			enemy_missiles_manager.Spawn(e.GetPosition(), { 0, 750 });
		}
	}

}

void EnemyManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Move remaining projectiles
	for (auto& e : enemies_)
	{
		target.draw(e);
	}
}


