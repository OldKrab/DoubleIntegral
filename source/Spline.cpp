#include "../headers/Spline.h"

// Public:

Spline::Spline(const dvector& xs_, const dvector& ys_) : ApproximationBase(xs_, ys_) {
    coefs_builded = false;
    n = xs_.size() -1;
    a = ys_;
    b = d = dvector(n + 1);
}

db Spline::get_value(db x) {
    if (!coefs_builded)
        build_coefs();
    int i = get_x_interval(x);
    return a[i] + b[i] * (x - xs[i]) + c[i] / 2 * pow(x - xs[i], 2) + d[i] / 6 * pow(x - xs[i], 3);
}

db Spline::get_derivative_value(db x) {
    if (!coefs_builded)
        build_coefs();
    int i = get_x_interval(x);
    return b[i]+ c[i] * (x - xs[i]) + d[i] / 2 * pow(x - xs[i], 2);
}

// Private:


void Spline::build_coefs() {
    calc_h();
    find_c();
    for (int i = 1; i <= n; ++i) {
        d[i] = (c[i] - c[i - 1]) / h[i];
        b[i] = h[i] / 2 * c[i] - h[i] * h[i] / 6 * d[i] + (ys[i] - ys[i - 1]) / h[i];
    }
    coefs_builded = true;
}

int Spline::get_x_interval(db x) const {
    if (x < xs[0])
        throw runtime_error("х outside of integration range! (less)");
    for (int i = 1; i <= n; i++)
        if (x <= xs[i] + 1e-5)
            return i;
    throw runtime_error("х outside of integration range! (more)");
}

void Spline::find_c() {
    if (h.empty())
        calc_h();
    dvector ca(n + 1, 0), cb(n + 1, 0), cc(n + 1, 0), cd(n + 1, 0);
    cb[0] = cb[n] = 1;
    for (int i = 1; i <= n - 1; i++) {
        ca[i] = h[i];
        cb[i] = -2 * (h[i] + h[i + 1]);
        cc[i] = h[i + 1];
        cd[i] = 6 * ((ys[i + 1] - ys[i]) / h[i + 1] - (ys[i] - ys[i - 1]) / h[i]);
    }
    c = sweep_method(ca, cb, cc, cd);
}

dvector Spline::sweep_method(dvector ca, dvector cb, dvector cc, dvector cd) const {
    dvector x(n + 1), alpha(n + 2), beta(n + 2);
    alpha[1] = cc[0] / cb[0];
    beta[1] = -cd[0] / cb[0];
    for (int i = 1; i <= n; ++i) {
        alpha[i + 1] = cc[i] / (cb[i] - ca[i] * alpha[i]);
        beta[i + 1] = (ca[i] * beta[i] - cd[i]) / (cb[i] - ca[i] * alpha[i]);
    }
    x[n] = beta[n + 1];
    for (int i = n - 1; i >= 1; --i)
        x[i] = alpha[i + 1] * x[i + 1] + beta[i + 1];
    x[0] = cc[0] / cb[0] * x[1] - cd[0] / cb[0];
    return x;
}

void Spline::calc_h() {
    h  = dvector(n+1);
    h[0] = 0;
    for (int i = 1; i <= n; i++)
        h[i] = xs[i] - xs[i - 1];
}




