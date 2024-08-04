#include <SFML/Graphics.hpp>
#include <cmath>
#include <complex>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int MAX_ITER = 1000;
constexpr double ZOOM = 1.0;
constexpr double MOVE_X = 0.0;
constexpr double MOVE_Y = 0.0;

sf::Color getColor(int n) {
    if (n == MAX_ITER)
        return sf::Color::Black;
    return sf::Color(255 - n % 256, 255 - n % 256, 255 - n % 256);
}

void drawJulia(sf::Image &image, const std::complex<double> &C) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            double real =
                1.5 * (x - WIDTH / 2.0) / (0.5 * ZOOM * WIDTH) + MOVE_X;
            double imag = (y - HEIGHT / 2.0) / (0.5 * ZOOM * HEIGHT) + MOVE_Y;
            std::complex<double> z(real, imag);

            int n = 0;
            while (std::abs(z) < 2.0 && n < MAX_ITER) {
                z = z * z + C;
                n++;
            }

            image.setPixel(x, y, getColor(n));
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),
                            "Julia Set Animation");

    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);

    sf::Clock clock;
    double angle = 0.0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 动态更新参数 C
        double realPart = 0.7885 * std::cos(angle);
        double imagPart = 0.7885 * std::sin(angle);
        std::complex<double> C(realPart, imagPart);

        drawJulia(image, C);
        texture.update(image);

        window.clear();
        window.draw(sprite);
        window.display();

        // 更新动画
        auto t = clock.getElapsedTime();
        // sf::Time elapsed = clock.restart();
        angle += t.asSeconds() * 0.5; // 调整旋转速度
    }

    return 0;
}
