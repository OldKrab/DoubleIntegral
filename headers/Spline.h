#ifndef DOUBLEINTEGRAL_SPLINE_H
#define DOUBLEINTEGRAL_SPLINE_H

#include "matrix.h"
#include "ApproximationBase.h"
#include <utility>
#include <valarray>


using namespace std;

class Spline : public ApproximationBase {
public:
    /// Вычислить значение сплайна в точке х
    db get_value(db x) override;

    Spline( const dvector& xs_,  const dvector& ys_);

    ~Spline(){};

private:
    /// Найти все коэффициенты
    void build_coefs();

    /// Найти индекс интервала, которому принадлежит х
    int get_x_interval(db x) const;

    /// Найти коэффициенты с
    void find_c();

    /// Метод прогонки для решения системы уравнений с трехдиагональной матрицей
    /// \param ca, cb, cc: Значения на трех диагоналях
    /// \param cd: Значения справа
    /// \return Решение системы
    dvector sweep_method(dvector ca, dvector cb, dvector cc, dvector cd) const;

    /// Посчитать интервалы h
    void calc_h();

    bool coefs_builded;
    dvector a, b, c, d, h;
    int n;
};


#endif