
#include "headers/PolygonDrawing.h"
#include "headers/Spline.h"
#include "headers/geometry.h"
#include "headers/SimpsonIntegral.h"
#include "headers/MonteCarloIntegral.h"
#include <iostream>

using namespace std;

dvector Range(int beg, int end) {
    dvector res(end - beg);
    for (int i = beg; i < end; i++)
        res[i - beg] = i;
    return res;
}

dvector dbRange(db beg, db end, int cnt) {
    dvector res(cnt);
    db interval = end - beg;
    for (int i = 0; i < cnt; i++)
        res[i] = beg + db(i) / (cnt - 1) * interval;
    return res;
}

vector<db> GetValuesOfFunc(dvector xs, function<db(db)> func) {
    vector<db> dots(xs.size());
    for (int i = 0; i < xs.size(); i++)
        dots[i] = func(xs[i]);
    return dots;
}

void InputPolygon(dvector &xs, dvector &ys) {
    PolygonDrawing pd({1, 1}, 50);
    pd.Show();
    pd.GetPolygonInArea(xs, ys);
}

void OutputPoints(ofstream &fout, const vector<Point> &p) {
    for (auto i : p)
        fout << i.x << ' ';
    fout << endl;
    for (auto i: p)
        fout << i.y << ' ';
    fout << endl;

}

vector<Point> MergeVectorsIntoPoints(const vector<db> &sx, const vector<db> &sy) {
    auto res = vector<Point>(sx.size());
    for (int i = 0; i < sx.size(); i++)
        res[i] = {sx[i], sy[i]};
    return res;
}

int main() {
    setlocale(LC_ALL, "rus");
    int montePointsCnt = 10000;
        int splinePointsCnt = 5001;
    auto input_file_name = R"(D:\GoogleDrive\sync\source\clion\DoubleIntegral\input.txt)";
    dvector xs, ys;
//    InputPolygon(xs, ys);
//        ofstream iout(input_file_name);
//    iout << xs << endl << ys << endl;
    ifstream iin(input_file_name);
    iin >> xs >> ys;

    auto t = Range(0, xs.size());
    Spline sp1(t, xs), sp2(t, ys);

    auto spl_t = dbRange(0, t.size() - 1, splinePointsCnt);
    auto spl_x = GetValuesOfFunc(spl_t, [sp1](db x) mutable { return sp1.get_value(x); });
    auto spl_y = GetValuesOfFunc(spl_t, [sp2](db x) mutable { return sp2.get_value(x); });

    auto points = MergeVectorsIntoPoints(spl_x, spl_y);

    auto x_der_y = GetValuesOfFunc(spl_t, [sp1, sp2](db x) mutable {
        return sp2.get_value(x) * sp1.get_derivative_value(x);
    });
    auto SimpsonArea = abs(SimpsonIntegral::CalcIntegral(MergeVectorsIntoPoints(spl_t, x_der_y)));


    Point leftDown = {*min_element(spl_x.begin(), spl_x.end()), *min_element(spl_y.begin(), spl_y.end())};
    Point rightUp = {*max_element(spl_x.begin(), spl_x.end()), *max_element(spl_y.begin(), spl_y.end())};
    MonteCarloIntegral2 mc(points, leftDown, rightUp);
    auto monteArea = mc.CalcIntegral(montePointsCnt, [](Point) { return 1; });
    auto monteX = mc.CalcIntegral(montePointsCnt, [](Point p) { return p.x; });
    auto monteY = mc.CalcIntegral(montePointsCnt, [](Point p) { return p.y; });

    vector<Point> inPoints, outPoints;
    mc.GetGeneratedPoints(inPoints, outPoints);

    auto file_name = R"(D:\GoogleDrive\sync\source\clion\DoubleIntegral\spline.txt)";
    ofstream fout(file_name);
    cout << "Area by Simpson: " << SimpsonArea << endl;
    cout << "Area by Monte-Carlo: " << monteArea << endl;
    OutputPoints(fout, points);
    OutputPoints(fout, inPoints);
    OutputPoints(fout, outPoints);
    fout << monteX / monteArea << endl << monteY / monteArea;
    fout.close();
    system(R"(python D:\GoogleDrive\sync\source\clion\DoubleIntegral\graph.py)");
    return 0;
}

