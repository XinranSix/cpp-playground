#include <SFML/Graphics.hpp>
#include <cmath> // 用于 std::sqrt 和 std::atan2

// 手动定义 M_PI
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr int ITERATIONS = 5; // 分形的递归深度

// 计算三角形的顶点
sf::Vector2f calculateKochPoint(const sf::Vector2f &start,
                                const sf::Vector2f &end) {
    sf::Vector2f delta = end - start;
    float length = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float angle = std::atan2(delta.y, delta.x);

    sf::Vector2f middle = start + 0.5f * delta;
    sf::Vector2f top =
        middle + sf::Vector2f(std::cos(angle - M_PI / 3) * length / 3.0f,
                              std::sin(angle - M_PI / 3) * length / 3.0f);

    return top;
}

// 递归绘制科赫曲线
void drawKochCurve(sf::RenderWindow &window, const sf::Vector2f &start,
                   const sf::Vector2f &end, int depth) {
    if (depth == 0) {
        sf::VertexArray line(sf::Lines, 2);
        line[0] = sf::Vertex(start, sf::Color::White);
        line[1] = sf::Vertex(end, sf::Color::White);
        window.draw(line);
    } else {
        sf::Vector2f a = start;
        sf::Vector2f b = calculateKochPoint(start, end);
        sf::Vector2f c = calculateKochPoint(end, start);
        sf::Vector2f d = end;

        drawKochCurve(window, a, b, depth - 1);
        drawKochCurve(window, b, c, depth - 1);
        drawKochCurve(window, c, d, depth - 1);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Koch Snowflake");

    // 科赫雪花的三个边
    sf::Vector2f p1(WIDTH / 2.0f, 50.0f);
    sf::Vector2f p2(WIDTH / 4.0f * 3.0f, HEIGHT - 50.0f);
    sf::Vector2f p3(WIDTH / 4.0f, HEIGHT - 50.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        // 绘制科赫雪花的三条边
        drawKochCurve(window, p1, p2, ITERATIONS);
        drawKochCurve(window, p2, p3, ITERATIONS);
        drawKochCurve(window, p3, p1, ITERATIONS);

        window.display();
    }

    return 0;
}
