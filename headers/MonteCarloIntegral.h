#ifndef DOUBLEINTEGRAL_MONTECARLOINTEGRAL_H
#define DOUBLEINTEGRAL_MONTECARLOINTEGRAL_H

#include "geometry.h"
#include <vector>
#include <functional>

class MonteCarloIntegral2 {
public:
    MonteCarloIntegral2(std::vector<Point> fig, Point leftDown, Point rightUp);

    db CalcIntegral(int n, std::function<db(Point)> func);

    void GetGeneratedPoints(std::vector<Point> &inPoints, std::vector<Point> &outPoints);

private:
    Point GetRandPoint() const;

    bool IsInFig(Point point);

    std::vector<Point> fig;
    std::vector<Point> inFigPoints;
    std::vector<Point> outFigPoints;
    Point leftDown, rightUp;
};


#endif //DOUBLEINTEGRAL_MONTECARLOINTEGRAL_H
