#include "../headers/ApproximationBase.h"

void ApproximationBase::out_dots(const string &file_out, db step) {
    ofstream fout(file_out);
    for (db x = xs[0]; x <= xs[xs.size() - 1]; x += step)
        fout << x << ' ';
    fout << xs[xs.size() - 1] << endl;
    for (db x = xs[0]; x <= xs[xs.size() - 1]; x += step)
        fout << get_value(x) << ' ';
    fout << get_value(xs[xs.size() - 1] );
}

ApproximationBase::ApproximationBase(dvector xs, dvector ys) : xs(move(xs)), ys(move(ys)) {}
