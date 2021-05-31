
#include "headers/PolygonDrawing.h"
#include "headers/Spline.h"
#include "headers/geometry.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

dvector Range(int beg, int end, int step = 1) {
    dvector res(end - beg);
    for (int i = beg; i < end; i += step)
        res[i - beg] = i;
    return res;
}

void InputPolygon(dvector &xs, dvector &ys) {
    PolygonDrawing pd({1, 1}, 150);
    pd.Show();
    pd.GetPolygonInArea(xs, ys);
}



vector<Point> ConvertToSpline(const dvector &xs, const dvector &ys, db step) {
    auto t = Range(0, xs.size());
    Spline sp1(t, xs), sp2(t, ys);
    auto n = int((db) xs.size() / step);
    auto res = vector<Point>(n+1);
    for(int i = 0; i < n; i++) {
        res[i].x = sp1.get_value(i * step);
        res[i].y = sp2.get_value(i * step);
    }
    res[n] = {sp1.get_value(xs.size()), sp2.get_value(xs.size())};
    return res;
}

int main() {
    setlocale(LC_ALL, "rus");
    dvector xs, ys;
    InputPolygon(xs, ys);
//    DrawSpline(xs,ys,0.01);

    return 0;
}

