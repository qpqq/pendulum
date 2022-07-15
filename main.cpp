#include "pendulum.hpp"

int main() {
    // antialiasing shapes
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 500),
                            "Particles",
                            sf::Style::Default,
                            settings);
    window.setVerticalSyncEnabled(true); // vertical synchronization

    // create the pendulum
    Pendulum pendulum(1, 200.f);

    // create a clock to track the elapsed time
    sf::Clock clock;

    // run the main loop
    while (window.isOpen()) {

        // handle events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                pendulum.press(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseMoved) {
                pendulum.move(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                pendulum.release(sf::Mouse::getPosition(window));
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space)
                    pendulum.hold();
            }
        }

        // update it
        sf::Time elapsed = clock.restart();
        pendulum.update(elapsed);

        // draw it
        window.clear();
        window.draw(pendulum);
        window.display();
    }
}
