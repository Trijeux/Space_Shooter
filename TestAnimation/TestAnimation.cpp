#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::Texture texture_no_move;
	sf::Texture texture_move;
	sf::Sprite sprite;

	sf::Texture texture_bg;
	sf::Sprite sprite_bg;

	sf::CircleShape itbox;

	itbox.setRadius(5);
	itbox.setFillColor(sf::Color::Green);

	texture_no_move.loadFromFile("assets/Touhou1.png");
	texture_move.loadFromFile("assets/Touhou3.png");
	sprite.setTexture(texture_no_move);

	texture_bg.loadFromFile("assets/Touhou2.png");
	sprite_bg.setTexture(texture_bg);

	sf::RenderWindow window(sf::VideoMode(sprite_bg.getGlobalBounds().width, sprite_bg.getGlobalBounds().height), "SFML works!");
	sf::CircleShape shape(100.f);

	sprite.setScale(2, 2);

	sprite.setOrigin(sprite.getGlobalBounds().width / 2 / sprite.getScale().x, sprite.getGlobalBounds().height / 2 / sprite.getScale().y);
	sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);

	itbox.setOrigin(itbox.getGlobalBounds().width / 2, itbox.getGlobalBounds().height / 2);

	bool flag_shift = false;
	float max_speed = 500.0f;
	float speed = max_speed;

	sf::Clock clock;
	float dt = 0.0f;
	float laser_cooldown = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			flag_shift = true;
			speed = max_speed / 2;
		}
		else
		{
			flag_shift = false;
			speed = max_speed;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sf::Vector2f direction;
			direction.y = -1;
			sf::Vector2f pos = sprite.getPosition() + speed * direction * dt;
			sprite.setPosition(pos);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sf::Vector2f direction;
			direction.y = +1;
			sf::Vector2f pos = sprite.getPosition() + speed * direction * dt;
			sprite.setPosition(pos);

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setScale(2, 2);
			sprite.setTexture(texture_no_move);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.setScale(2, 2);
			sprite.setTexture(texture_move);
			sf::Vector2f direction;
			direction.x = -1;
			sf::Vector2f pos = sprite.getPosition() + speed * direction * dt;
			sprite.setPosition(pos);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setTexture(texture_move);
			sprite.setScale(-2, 2);
			sf::Vector2f direction;
			direction.x = +1;
			sf::Vector2f pos = sprite.getPosition() + speed * direction * dt;
			sprite.setPosition(pos);
		}
		else
		{
			sprite.setScale(2, 2);
			sprite.setTexture(texture_no_move);
		}

		itbox.setPosition(sprite.getPosition().x, sprite.getPosition().y);

		window.clear();
		window.draw(sprite_bg);
		window.draw(sprite);
		if (flag_shift)
		{
			window.draw(itbox);
		}
		window.display();

		laser_cooldown += dt;
		dt = clock.restart().asSeconds();
	}

	return 0;
}