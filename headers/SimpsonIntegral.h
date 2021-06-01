#ifndef DOUBLEINTEGRAL_SIMPSONINTEGRAL_H
#define DOUBLEINTEGRAL_SIMPSONINTEGRAL_H
#include "geometry.h"
#include <functional>

class SimpsonIntegral {
public:
    static db CalcIntegral(std::vector<Point> points);
};


#endif //DOUBLEINTEGRAL_SIMPSONINTEGRAL_H
