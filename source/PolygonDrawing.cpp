#include "../headers/PolygonDrawing.h"

// Public:

PolygonDrawing::PolygonDrawing(sf::Vector2f area, int timeDeltaMs) : area(area), timeDeltaMs(timeDeltaMs) {}

void PolygonDrawing::Show() {
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
                            "Draw polygon", sf::Style::Close);
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
        if (isMousePressed && clock.getElapsedTime().asMilliseconds() > timeDeltaMs) {
            // Painting
            auto &&dot = sf::Vector2f(sf::Mouse::getPosition(window));
            if (IsUniqueDot(dot)) {
                UpdatePolygon(dot);
                clock.restart();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(polygon);

        window.display();
    }
}

void PolygonDrawing::GetPolygonInArea(dvector &crdX, dvector &crdY) {
    auto cnt = polygon.getVertexCount();
    crdX = dvector(cnt);
    crdY = dvector(cnt);
    double convertCoefX = (double) area.x / windowSize.x;
    double convertCoefY = (double) area.y / windowSize.y;
    for (int i = 0; i < cnt; i++) {
        crdX[i] = polygon[i].position.x * convertCoefX;
        crdY[i] = area.y - polygon[i].position.y * convertCoefY;
    }
}


// Private:


bool PolygonDrawing::IsUniqueDot(const sf::Vector2f &dot) {
    auto cnt = polygon.getVertexCount();
    if(cnt < 2) return true;
    auto lastDot = polygon[cnt-2].position;
    return lastDot != dot;
}

void PolygonDrawing::UpdatePolygon(sf::Vector2f dot) {
    auto cnt = polygon.getVertexCount();
    HandleDotWithBorders(dot);
    if (cnt == 0) {
        polygon.append(dot);
        polygon.append(dot);
    }
    else {
        polygon[cnt - 1] = sf::Vector2f(dot);
        polygon.append(polygon[0]);
    }
}

void PolygonDrawing::HandleDotWithBorders(sf::Vector2f &dot) const {
    if (dot.x < 0) dot.x = 0;
    if (dot.x > float(windowSize.x)) dot.x = float(windowSize.x);
    if (dot.y < 0) dot.y = 0;
    if (dot.y > float(windowSize.y)) dot.y = float(windowSize.y);
}
