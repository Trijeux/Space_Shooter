#include "projectile_manager.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

#include "asteroid.h"
#include "starship.h"

constexpr float kCooldownLimit = 0.15f;

void ProjectileManager::Spawn(const sf::Vector2f spawn_position, sf::Vector2f direction, sf::Sound& sound, const int rotate)
{

	if (cooldown_dt_ < kCooldownLimit)
		return;

	sound.play();
	projectiles_.emplace_back(direction);
	projectiles_.back().SetPosition(spawn_position);
	projectiles_.back().SetScale(1, rotate);
	cooldown_dt_ = 0;

}

void ProjectileManager::Refresh(const float dt, const sf::Vector2u& window_size)
{

	cooldown_dt_ += cooldown_timer_.restart().asSeconds();

	if (const auto removed_elt = std::ranges::remove_if(projectiles_,[](const Projectile& p) {return p.IsDead(); }).begin(); removed_elt != projectiles_.end())
	{
		projectiles_.erase(removed_elt, projectiles_.end());
	}

	for (Projectile& p : projectiles_)
	{
		p.Move(dt, window_size);
	}
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




