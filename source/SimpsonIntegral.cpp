#include "../headers/SimpsonIntegral.h"


db SimpsonIntegral::CalcIntegral(std::vector<Point> points) {

    db res = 0;
    for (int i = 0; i < points.size() - 2; i+=2) {
        db h = points[i + 1].x - points[i].x;
        res += h * (points[i].y + 4 * points[i+1].y + points[i + 2].y);
    }
    return 1. / 3 * res;
}
