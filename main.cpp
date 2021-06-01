
#include "headers/PolygonDrawing.h"
#include "headers/Spline.h"
#include "headers/geometry.h"
#include "headers/SimpsonIntegral.h"
#include <iostream>

using namespace std;

dvector Range(int beg, int end) {
    dvector res(end - beg);
    for (int i = beg; i < end; i ++)
        res[i - beg] = i;
    return res;
}

dvector dbRange(db beg, db end, int cnt){
    dvector res(cnt);
    db interval = end - beg;
    for (int i = 0; i < cnt; i++)
        res[i] = beg + db(i) / (cnt - 1) * interval;
    return res;
}

vector<Point> GetPoints(dvector xs, function<db(db)> func) {
    vector<Point> dots(xs.size());
    for (int i = 0; i < xs.size(); i++) {
        db y = func(xs[i]);
        dots[i] = {xs[i], y};
    }
    return dots;
}

void InputPolygon(dvector &xs, dvector &ys) {
    PolygonDrawing pd({2, 2}, 50);
    pd.Show();
    pd.GetPolygonInArea(xs, ys);
}

void OutputRes(const vector<Point>& p)
{
    auto file_name = R"(D:\GoogleDrive\sync\source\clion\DoubleIntegral\spline.txt)";
    ofstream fout(file_name);
    for (auto i : p)
        fout << i.x << ' ';
    fout << endl;
    for (auto i: p)
        fout << i.y << ' ';
    fout.close();
}

vector<Point> MergeSplines(const vector<Point>& sx, const  vector<Point>& sy){
    auto res = vector<Point>(sx.size());
    for(int i = 0; i < sx.size(); i++)
        res[i] = {sx[i].y, sy[i].y};
    return res;
}

int main() {
    setlocale(LC_ALL, "rus");
    dvector xs, ys;
    InputPolygon(xs, ys);

    auto t = Range(0, xs.size());
    Spline sp1(t, xs), sp2(t, ys);

    auto spl_t = dbRange(0, t.size()-1, 1000);
    auto spl_x = GetPoints(spl_t, [sp1] (db x) mutable{return sp1.get_value(x);});
    auto spl_y = GetPoints(spl_t, [sp2] (db x) mutable{return sp2.get_value(x);});

    auto points = MergeSplines(spl_x, spl_y);

    auto x_der_y = GetPoints(spl_t, [sp1, sp2] (db x) mutable{return sp2.get_value(x) * sp1.get_derivative_value(x);});
    auto area = abs(SimpsonIntegral::CalcIntegral(x_der_y));



    cout << "Area by Simpson: " << area << endl;
    OutputRes(points);
    system(R"(python D:\GoogleDrive\sync\source\clion\DoubleIntegral\graph_task3.py)");
    return 0;
}

