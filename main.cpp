#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

sf::Vector2f clamp(sf::Vector2f min, sf::Vector2f max, float width, float height, sf::Vector2f val) {
    float x, y;
    if (val.x < min.x) {
        x = min.x;
    } else if (val.x > max.x - width) {
        x = max.x - width;
    } else {
        x = val.x;
    }
    if (val.y < min.y) {
        y = min.y;
    } else if (val.y > max.y - height) {
        y = max.y - height;
    } else {
        y = val.y;
    }
    return sf::Vector2f(x, y);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),  "Psychic Dangerzone");
    window.setVerticalSyncEnabled(true);

    sf::Vector2f min_bounds(0, 0);
    sf::Vector2f max_bounds(800, 600);

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
        player.setPosition(clamp(min_bounds, max_bounds, player.getRadius() * 2, player.getRadius() * 2, player.getPosition()));

        window.clear(sf::Color::Black);

        window.draw(player);

        window.display();
        std::cout << world_clock.getElapsedTime().asSeconds() - last_frame_time << std::endl;
    }

    return 0;
}
