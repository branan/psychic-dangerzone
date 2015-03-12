#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),  "Psychic Dangerzone");
    window.setVerticalSyncEnabled(true);

    sf::Clock world_clock;

    sf::CircleShape player(50);

    float last_frame_time;
    while(window.isOpen()) {
        last_frame_time = world_clock.getElapsedTime().asSeconds();

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2f velocity;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
          velocity.x -= 10;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
          velocity.x += 10;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          velocity.y -= 10;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          velocity.y += 10;
        }

        player.move(velocity);
        //player.move(velocity.x, velocity.y);

        window.clear(sf::Color::Black);

        window.draw(player);

        window.display();
        std::cout << world_clock.getElapsedTime().asSeconds() - last_frame_time << std::endl;
    }

    return 0;
}
