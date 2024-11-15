#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H
#include <vector>

#include "enemy.h"
#include "projectile_manager.h"

class EnemyManager final : public sf::Drawable
{

private:
	std::vector<Enemy> enemies_;
	float spawn_dt_ = 0;

public:
	std::vector<Enemy>& GetEntities() { return enemies_; }
	void Refresh(float dt, const sf::Vector2u& window_size, ProjectileManager& enemy_missiles_manager);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif // ENEMY_MANAGER_H
