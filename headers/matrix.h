#ifndef DOUBLEINTEGRAL_MATRIX_H
#define DOUBLEINTEGRAL_MATRIX_H

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

typedef  double db;
typedef vector<db> dvector;
typedef vector<dvector> dmatrix;


// Output vector
template <class T>
ostream& operator<<(ostream& out, const vector<T>& v)
{
    for (double el : v) {
        out << right << setw(8) << el << ' ';
    }
    return out;
}

// Input vector
template <class T>
istream& operator>>(istream& in, vector<T>& v)
{
    string s;
    getline(in, s);
    stringstream ss(s);
    while(!ss.eof()){
        T num;
        ss >> num;
        v.push_back(num);
    }
    return in;
}

// Сложение векторов
template <class T>
dvector operator+(const vector<T>& a, const vector<T>& b)
{
    dvector res = a;
    for (int i = 0; i < a.size(); i++)
        res[i] += b[i];
    return res;
}

// Умножение вектора на число
dvector operator*(const dvector& a, const db num);

// Умножение матрицы на вектор
dvector operator*(const dmatrix& a, const dvector& x);

// Умножение матрицы на другую матрицу
dmatrix operator*(const dmatrix& a, const dmatrix& b);

#endif