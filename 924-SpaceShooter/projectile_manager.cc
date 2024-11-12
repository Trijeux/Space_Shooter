#include "projectile_manager.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

#include "asteroid.h"

constexpr float kCooldown_limit_ = 0.15f;

void ProjectileManager::Spawn(sf::Vector2f spawn_position, sf::Vector2f direction)
{

	if (cooldwon_dt_ < kCooldown_limit_)
		return;

	projectiles_.emplace_back(direction);
	projectiles_.back().SetPosition(spawn_position);
	cooldwon_dt_ = 0;

}

void ProjectileManager::Refresh(float dt, const sf::Vector2u& window_size)
{

	cooldwon_dt_ += cooldown_timer_.restart().asSeconds();
	//std::cout << "Cooldown Timer : " << cooldwon_dt_ << '\n';


	// Cleaning unused projectiles
	auto removed_elt = std::remove_if(
		projectiles_.begin(),
		projectiles_.end(),
		[](const Projectile& p) {return p.IsDead(); }
	);

	if (removed_elt != projectiles_.end())
	{
		projectiles_.erase(removed_elt, projectiles_.end());
	}

	//erase_if(projectiles_, [](const Projectile& p) {return p.IsDead(); });

	// Move remaining projectiles
	for (Projectile& p : projectiles_)
	{
		p.Move(dt, window_size);
	}

	//std::cout << "nb projectiles ? " << projectiles_.size() << '\n';

}

bool ProjectileManager::CheckCollisions(std::vector<Asteroid>& asteroids)
{
	for (auto& p : projectiles_)
	{
		for (auto& a : asteroids)
		{
			if (p.IsDead() == false && a.IsDead() == false && p.Intersects(a.HitBox()))
			{
				p.SetDeath();
				a.SetDeath();
				return true;
			}
		}
	}
	return false;
}

bool ProjectileManager::CheckCollisions(std::vector<Enemy>& enemies)
{
	for (auto& p : projectiles_)
	{
		for (auto& e : enemies)
		{
			if (p.IsDead() == false && e.IsDead() == false && p.Intersects(e.HitBox()))
			{
				p.SetDeath();
				return e.Damage(1);
			}
		}
	}
	return false;
}

void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Move remaining projectiles
	for (const Projectile& p : projectiles_)
	{
		target.draw(p);
	}
}




