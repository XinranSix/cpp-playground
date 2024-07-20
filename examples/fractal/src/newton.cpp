#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int MAX_ITER = 50;
constexpr double ZOOM = 1.0;
constexpr double MOVE_X = 0.0;
constexpr double MOVE_Y = 0.0;

std::complex<double> newtonIteration(const std::complex<double> &z,
                                     const std::complex<double> &c) {
    return z - (z * z * z - c) / (3.0 * z * z);
}

sf::Color getColor(int n) {
    return sf::Color(255 - (n * 5) % 255, 255 - (n * 7) % 255,
                     255 - (n * 11) % 255);
}

void drawFractal(sf::Image &image, const std::complex<double> &c) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real =
                1.5 * (x - WIDTH / 2.0) / (0.5 * ZOOM * WIDTH) + MOVE_X;
            double imag = (y - HEIGHT / 2.0) / (0.5 * ZOOM * HEIGHT) + MOVE_Y;
            std::complex<double> z(real, imag);

            int n = 0;
            while (n < MAX_ITER) {
                z = newtonIteration(z, c);
                if (std::abs(z * z * z - c) < 0.0001)
                    break;
                n++;
            }

            image.setPixel(x, y, getColor(n));
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Newton Fractal");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    // Example with c = 1 (you can change this to other constants to explore
    // different patterns)
    std::complex<double> c(1.0, 0.0);
    drawFractal(image, c);

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
