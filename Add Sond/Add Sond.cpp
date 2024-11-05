#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

int main()
{
    sf::SoundBuffer sound_buffer;
    sf::Sound sound;

    sf::Music music;

    music.openFromFile("asset/Furrýmon_ Gotta.mp3");
	music.setLoop(true);
	music.play();

    sound_buffer.loadFromFile("asset/sfx_wpn_laser8.wav");
    sound.setBuffer(sound_buffer);

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sound.play();
            }
            if (sf::Joystick::isButtonPressed(0, 0))
            {
                sound.play();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}