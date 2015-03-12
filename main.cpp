#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600),  "Psychic Dangerzone");

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            // TODO: process events
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
