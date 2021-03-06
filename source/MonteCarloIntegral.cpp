#include "../headers/MonteCarloIntegral.h"
#include <utility>

MonteCarloIntegral2::MonteCarloIntegral2(std::vector<Point> fig, Point leftDown, Point rightUp)
        : fig(std::move(fig)), leftDown(leftDown), rightUp(rightUp) {
    srand(time(0));
}

db MonteCarloIntegral2::CalcIntegral(int n, std::function<db(Point)> func) {
    db res = 0;
    inFigPoints.clear();
    outFigPoints.clear();
    for (int i = 0; i < n; ++i) {
        auto point = GetRandPoint();
        if (IsInFig(point)) {
            res += func(point);
            inFigPoints.push_back(point);
        } else
            outFigPoints.push_back(point);
    }
    db limArea = (rightUp.x - leftDown.x) * (rightUp.y - leftDown.y);
    return res / n * limArea;
}

Point MonteCarloIntegral2::GetRandPoint() const {
    int mx = 10000;
    db x = leftDown.x + db(rand() % mx) / mx * (rightUp.x - leftDown.x);
    db y = leftDown.y + db(rand() % mx) / mx * (rightUp.y - leftDown.y);
    return Point{x, y};
}

bool MonteCarloIntegral2::IsInFig(Point point) {
    int interCnt = 0;
    Segment cur{point, {rightUp.x, point.y}};
    for (int i = 0; i < fig.size() - 1; i++) {
        Segment line{fig[i], fig[i + 1]};
        if (cur.Intersect(line))
            interCnt++;
    }
    return interCnt % 2;
}

void MonteCarloIntegral2::GetGeneratedPoints(std::vector<Point> &inPoints, std::vector<Point> &outPoints) {
    inPoints = inFigPoints;
    outPoints = outFigPoints;
}


