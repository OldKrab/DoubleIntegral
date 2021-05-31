#pragma once

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

typedef double db;


struct Point {
    db x, y;

    bool operator<(Point b) const;
};

struct Segment;

struct Vector {
    db x, y;

    Vector(db x, db y);

    explicit Vector(Segment s);

    Vector(Point a, Point b);

    db VectorProd(Vector b) const;
};

struct Segment {
    Point a, b;

    Segment(Point a, Point b);

    bool Intersect(Segment b);
};

