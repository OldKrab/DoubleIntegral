#ifndef DOUBLEINTEGRAL_POLYGONDRAWING_H
#define DOUBLEINTEGRAL_POLYGONDRAWING_H

#include <SFML/Graphics.hpp>
#include "matrix.h"

class PolygonDrawing {
public:
    PolygonDrawing(sf::Vector2f area, int timeDeltaMs);

    void Show();

    void GetPolygonInArea(dvector &crdX, dvector &crdY);

private:
    bool IsUniqueDot(const sf::Vector2f& dot);

    void UpdatePolygon(sf::Vector2f dot);

    void HandleDotWithBorders(sf::Vector2f &dot) const;

    sf::VertexArray polygon{sf::PrimitiveType::LineStrip};
    int timeDeltaMs = 50;
    sf::Vector2f area;
    sf::Vector2i windowSize = {500, 500};
};


#endif //DOUBLEINTEGRAL_POLYGONDRAWING_H
