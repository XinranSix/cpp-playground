#include <SFML/Graphics.hpp>
#include <random>
 
constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int POINTS = 100000; 

sf::Vector2f barnsleyFernTransform(const sf::Vector2f &point) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);
    double r = dis(gen);

    if (r < 0.01) {
        return sf::Vector2f(0.0, 0.16 * point.y);
    } else if (r < 0.86) {
        return sf::Vector2f(0.85 * point.x + 0.04 * point.y,
                            -0.04 * point.x + 0.85 * point.y + 1.6);
    } else if (r < 0.93) {
        return sf::Vector2f(0.2 * point.x - 0.26 * point.y,
                            0.23 * point.x + 0.22 * point.y + 1.6);
    } else {
        return sf::Vector2f(-0.15 * point.x + 0.28 * point.y,
                            0.26 * point.x + 0.24 * point.y + 0.44);
    }
}

void drawBarnsleyFern(sf::Image &image) {
    sf::Vector2f point(0, 0);

    for (int i = 0; i < POINTS; ++i) {
        point = barnsleyFernTransform(point);

        int x = static_cast<int>((point.x + 3) * WIDTH / 6);
        int y = static_cast<int>((10 - point.y) * HEIGHT / 10);

        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            image.setPixel(x, y, sf::Color::Green);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Barnsley Fern");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    drawBarnsleyFern(image);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
