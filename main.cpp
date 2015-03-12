#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

sf::Vector2f clamp(sf::Vector2f min, sf::Vector2f max, float width, float height, sf::Vector2f val) {
    float x = std::max(min.x, std::min(max.x - width, val.x));
    float y = std::max(min.y, std::min(max.y - width, val.y));

    return sf::Vector2f(x, y);
}

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800,600),  "Psychic Dangerzone");
    window.setVerticalSyncEnabled(true);

    sf::Vector2f min_bounds(0, 0);
    sf::Vector2f max_bounds(800, 600);

    sf::Clock world_clock;

    sf::CircleShape player(50);

    std::vector<sf::CircleShape> enemies(4);
    for (int i = 0; i < 4; i++) {
      sf::CircleShape enemy(20, 4);
      enemy.setPosition(rand() % 790, rand() % 590);
      enemies.push_back(enemy);
    }

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

        std::for_each(enemies.begin(), enemies.end(),  [&](sf::CircleShape shape) -> void { window.draw(shape); });

        window.display();
        std::cout << world_clock.getElapsedTime().asSeconds() - last_frame_time << std::endl;
    }

    return 0;
}
