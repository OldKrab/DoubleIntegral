#include "../headers/matrix.h"

dvector operator*(const dvector &a, const db num) {
    dvector res = a;
    for (int i = 0; i < a.size(); i++)
        res[i] *= num;
    return res;
}

dvector operator*(const dmatrix &a, const dvector &x) {
    int m = a.size();
    dvector r(m, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            r[i] += a[i][j] * x[j];
    return r;
}

dmatrix operator*(const dmatrix &a, const dmatrix &b) {
    dmatrix res(a.size(), dvector(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b[0].size(); j++)
            for (int k = 0; k < b.size(); k++)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}
