#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),  "Psychic Dangerzone");
    window.setVerticalSyncEnabled(true);

    sf::Clock world_clock;

    float last_frame_time;
    while(window.isOpen()) {
        last_frame_time = world_clock.getElapsedTime().asSeconds();

        sf::Event event;
        while(window.pollEvent(event)) {
            // TODO: process events
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
        std::cout << world_clock.getElapsedTime().asSeconds() - last_frame_time << std::endl;
    }

    return 0;
}
