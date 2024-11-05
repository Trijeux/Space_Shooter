#include "projectile_manager.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>


ProjectileManager::ProjectileManager()
{
	sfx.loadFromFile("Assets/laser.mp3");

}
void ProjectileManager::Spawn(sf::Vector2f spawn_position)
{
	projectiles_.emplace_back();
	projectiles_.back().setPosition(spawn_position);
	//sound_projectile.setBuffer(sfx);
	//sound_projectile.play();

}

void ProjectileManager::Refresh(float dt_, const sf::Vector2u& window_size)
{
	//Clean unused projectiles
	auto removed_elt = std::remove_if(projectiles_.begin(), projectiles_.end(), [](const Projectile & p) { return p.IsDead(); });
	if (removed_elt != projectiles_.end())
	{
		projectiles_.erase(removed_elt);
	}

	//Move remaining projectiles
	for (Projectile& p : projectiles_)
	{
		p.Move(dt_, window_size);
	}
     //  	std::cout << "nb projectiles ? " << projectiles_.size() << '\n';
}
void ProjectileManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Projectile p : projectiles_)
	{
		target.draw(p);
	}
}