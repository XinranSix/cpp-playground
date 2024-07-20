#include <SFML/Graphics.hpp>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

void drawSierpinski(sf::RenderWindow &window, const sf::Vector2f &p1,
                    const sf::Vector2f &p2, const sf::Vector2f &p3, int depth) {
    if (depth == 0) {
        sf::VertexArray triangle(sf::Triangles, 3);
        triangle[0] = sf::Vertex(p1, sf::Color::White);
        triangle[1] = sf::Vertex(p2, sf::Color::White);
        triangle[2] = sf::Vertex(p3, sf::Color::White);
        window.draw(triangle);
    } else {
        sf::Vector2f mid12 = (p1 + p2) / 2.0f;
        sf::Vector2f mid23 = (p2 + p3) / 2.0f;
        sf::Vector2f mid31 = (p3 + p1) / 2.0f;

        drawSierpinski(window, p1, mid12, mid31, depth - 1);
        drawSierpinski(window, mid12, p2, mid23, depth - 1);
        drawSierpinski(window, mid31, mid23, p3, depth - 1);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
                            "Sierpinski Triangle");

    sf::Vector2f p1(WIDTH / 2.0f, 50.0f);
    sf::Vector2f p2(50.0f, HEIGHT - 50.0f);
    sf::Vector2f p3(WIDTH - 50.0f, HEIGHT - 50.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        drawSierpinski(window, p1, p2, p3,
                       7); // Depth of 5 for the Sierpinski Triangle
        window.display();
    }

    return 0;
}
