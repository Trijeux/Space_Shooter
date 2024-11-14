#ifndef ASTEROID_MANAGER_H
#define ASTEROID_MANAGER_H
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>

#include "asteroid.h"

class AsteroidManager : public sf::Drawable
{

private:
	std::vector<Asteroid> asteroids_;
	sf::Clock timer_;
	float time_elapsed_ = 0;
	float rotation_ = 0;

	const float kRotationfram = 0.02f;
public:
	void Refresh(float dt, const sf::Vector2u& window_size);
	std::vector<Asteroid>& GetEntities() { return asteroids_; }

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;



};

#endif // ASTEROID_MANAGER_H
