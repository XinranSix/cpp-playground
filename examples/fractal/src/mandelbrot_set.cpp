#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAX_ITER = 1000;

int mandelbrot(const std::complex<double> &c) {
    std::complex<double> z = 0;
    int n = 0;
    while (abs(z) <= 2 && n < MAX_ITER) {
        z = z * z + c;
        n++;
    }
    return n;
}

void drawFractal(sf::Image &image) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double imag = (y - HEIGHT / 2.0) * 4.0 / HEIGHT;
            std::complex<double> c(real, imag);
            int n = mandelbrot(c);

            int color = (n == MAX_ITER) ? 0 : (255 * n / MAX_ITER);
            sf::Color pixelColor(color, color, color);
            image.setPixel(x, y, pixelColor);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Fractal");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    drawFractal(image);

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
