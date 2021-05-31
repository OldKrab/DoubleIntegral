#ifndef DOUBLEINTEGRAL_APPROX_H
#define DOUBLEINTEGRAL_APPROX_H

#include <fstream>
#include "matrix.h"

using namespace std;

class ApproximationBase {
public:
    virtual db get_value(db x) = 0;

    void out_dots(const string &file_out, db step);

    ApproximationBase(dvector xs, dvector ys);

protected:
    dvector xs, ys;
};

#endif
