#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int ITERATIONS = 16;
constexpr double SCALE = 5.0;

void generateDragonCurve(std::vector<sf::Vertex> &vertices, int iterations) {
    std::vector<int> directions = { 1 }; // Start with a single right turn

    for (int i = 1; i < iterations; ++i) {
        std::vector<int> newDirections(directions);
        newDirections.push_back(1); // Always add a right turn

        // Add the reverse of the current directions with each turn inverted
        for (auto it = directions.rbegin(); it != directions.rend(); ++it) {
            newDirections.push_back(-(*it));
        }

        directions = newDirections;
    }

    sf::Vector2f position(WIDTH / 2, HEIGHT / 2);
    sf::Vector2f direction(SCALE, 0);

    vertices.push_back(sf::Vertex(position, sf::Color::White));
    for (int turn : directions) {
        direction = sf::Vector2f(direction.y * turn, -direction.x * turn);
        position += direction;
        vertices.push_back(sf::Vertex(position, sf::Color::White));
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dragon Curve");
    std::vector<sf::Vertex> vertices;

    generateDragonCurve(vertices, ITERATIONS);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
        window.display();
    }

    return 0;
}
