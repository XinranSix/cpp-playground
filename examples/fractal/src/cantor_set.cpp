#include <SFML/Graphics.hpp>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int ITERATIONS = 10;

void drawCantorSet(sf::RenderWindow &window, float x, float y, float length,
                   int depth) {
    if (depth == 0) {
        sf::VertexArray line(sf::Lines, 2);
        line[0] = sf::Vertex(sf::Vector2f(x, y));
        line[1] = sf::Vertex(sf::Vector2f(x + length, y));
        window.draw(line);
    } else {
        float third = length / 3.0f;
        drawCantorSet(window, x, y, third, depth - 1);
        drawCantorSet(window, x + 2 * third, y, third, depth - 1);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Cantor Set");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        drawCantorSet(window, 50.0f, HEIGHT / 2.0f, WIDTH - 100.0f, ITERATIONS);
        window.display();
    }

    return 0;
}
