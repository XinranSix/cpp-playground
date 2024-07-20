#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int MAX_ITER = 1000;
constexpr double ZOOM = 1.0;
constexpr double MOVE_X = -0.5;
constexpr double MOVE_Y = -0.5;

int burningShip(const std::complex<double>& c) {
    std::complex<double> z = 0;
    int n = 0;
    while (abs(z) <= 2 && n < MAX_ITER) {
        z = std::complex<double>(std::abs(z.real()), std::abs(z.imag()));
        z = z * z + c;
        n++;
    }
    return n;
}

void drawFractal(sf::Image& image) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real = 1.5 * (x - WIDTH / 2.0) / (0.5 * ZOOM * WIDTH) + MOVE_X;
            double imag = (y - HEIGHT / 2.0) / (0.5 * ZOOM * HEIGHT) + MOVE_Y;
            std::complex<double> c(real, imag);
            int n = burningShip(c);
            
            int color = (n == MAX_ITER) ? 0 : (255 * n / MAX_ITER);
            sf::Color pixelColor(color, color, color);
            image.setPixel(x, y, pixelColor);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Burning Ship Fractal");
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
