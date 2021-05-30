#ifndef DOUBLEINTEGRAL_POLYGONDRAWING_H
#define DOUBLEINTEGRAL_POLYGONDRAWING_H

#include <SFML/Graphics.hpp>

class PolygonDrawing {
public:
    PolygonDrawing(sf::Vector2f area) : area(area) {}

    void Show() {
        sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                                "Draw polygon",
                                sf::Style::Close);

        sf::Clock clock;
        bool isMousePressed = false;

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event))
                if (event.type == sf::Event::Closed)
                    // Close Window
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    // Start input
                    isMousePressed = true;
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    // End input
                    isMousePressed = false;
                }
            if (isMousePressed &&
                clock.getElapsedTime().asMilliseconds() > timeDeltaMs) {
                // Painting
                UpdatePolygon(sf::Vector2f(sf::Mouse::getPosition(window)));
                clock.restart();
            }

            window.clear(sf::Color::Black);
            window.draw(polygon);

            window.display();
        }
    }

private:
    void UpdatePolygon(sf::Vector2f dot){
        auto cnt = polygon.getVertexCount();
        HandleDotWithBorders(dot);
        if (cnt == 0)
            polygon.append(dot);
        else {
            polygon[cnt - 1] = sf::Vector2f(dot);
            polygon.append(polygon[0]);
        }
    }

    void HandleDotWithBorders(sf::Vector2f &dot) const {
        if (dot.x < 0) dot.x = 0;
        if (dot.x > float(windowSize.x)) dot.x = float(windowSize.x);
        if (dot.y < 0) dot.y = 0;
        if (dot.y > float(windowSize.y)) dot.y = float(windowSize.y);
    }

    sf::VertexArray polygon{sf::PrimitiveType::LineStrip};
    int timeDeltaMs = 50;
    sf::Vector2f area;
    sf::Vector2i windowSize = {500, 500};
};


#endif //DOUBLEINTEGRAL_POLYGONDRAWING_H
