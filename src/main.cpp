#include <BLIB/Logging.hpp>
#include <BLIB/Media/Shapes.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(
        sf::VideoMode(800, 600, 32), "BLIB Project", sf::Style::Close | sf::Style::Titlebar);
    BL_LOG_INFO << "Window opened";

    bl::shapes::Triangle triangle({0, 0}, {120, 0}, {60, 120});
    triangle.setPosition(400, 300);
    triangle.setFillColor(sf::Color::Red);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                BL_LOG_INFO << "Window closed";
                break;
            }
        }

        triangle.rotate(1.5f);

        window.clear(sf::Color::Cyan);
        window.draw(triangle);
        window.display();
        sf::sleep(sf::milliseconds(30));
    }

    BL_LOG_INFO << "Exiting";
    return 0;
}
