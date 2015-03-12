#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

sf::Vector2f clamp(sf::Vector2f min, sf::Vector2f max, float width, float height, sf::Vector2f val) {
    float x = std::max(min.x, std::min(max.x - width, val.x));
    float y = std::max(min.y, std::min(max.y - width, val.y));

    return sf::Vector2f(x, y);
}

float distance(sf::Vector2f lhs, sf::Vector2f rhs) {
  float x_delta = lhs.x - rhs.x;
  float y_delta = lhs.y - rhs.y;
  return sqrt(x_delta * x_delta + y_delta * y_delta);
}

bool colliding(sf::Vector2f a_pos, float a_size, sf::Vector2f b_pos, float b_size) {
  sf::Vector2f a_center(a_pos.x + a_size, a_pos.y + a_size);
  sf::Vector2f b_center(b_pos.x + b_size, b_pos.y + b_size);

  return distance(a_center, b_center) < (a_size + b_size);
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
      float x = rand() % 790;
      float y = rand() % 590;
      std::cout << "creating: " << x << " " << y << std::endl;
      enemy.setPosition(x, y);
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

        auto remaining = std::remove_if(enemies.begin(), enemies.end(), [& player](sf::CircleShape enemy) -> bool {
            return colliding(enemy.getPosition(), enemy.getRadius(), player.getPosition(), player.getRadius());
        });

        enemies.erase(remaining, enemies.end());

        std::for_each(enemies.begin(), enemies.end(),  [&](sf::CircleShape enemy) -> void {
            window.draw(enemy);
        });

        window.display();
    }

    return 0;
}
