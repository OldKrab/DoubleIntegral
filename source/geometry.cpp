
#include "../headers/geometry.h"

db eps = 1e-3;


/// --- Point definitions --- \\\

bool Point::operator<(Point b) const {
    return x < b.x + eps || x - b.x < eps && y < b.y + eps;
}


/// --- Vector definitions --- \\\

Vector::Vector(db x, db y) : x(x), y(y) {}

Vector::Vector(Segment s) : Vector(s.b.x - s.a.x, s.b.y - s.a.y) {}

Vector::Vector(Point a, Point b) : Vector(b.x - a.x, b.y - a.y) {}

db Vector::VectorProd(Vector b) const {
    return x * b.y - b.x * y;
}


/// --- Segment definitions --- \\\

Segment::Segment(Point a, Point b) : a(a), b(b) {}

// !!! Doesn't work with segments on same line (todo)
bool Segment::Intersect(Segment s2) {
    Vector ab{*this}, cd{s2}, ac{a, s2.a}, ad{a, s2.b}, ca{s2.a, a}, cb{s2.a, b};
    return ab.VectorProd(ac) * ab.VectorProd(ad) <= 0 && cd.VectorProd(ca) * cd.VectorProd(cb) <= 0;
}


