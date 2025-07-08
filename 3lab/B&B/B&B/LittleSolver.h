#pragma once
#ifndef LITTLESOLVER_H
#define LITTLESOLVER_H

#include "MatrixD.h"
#include <list>
#include <utility>
#include <limits>

class LittleSolver {
public:
    LittleSolver(const MatrixD& initialMatrix);

    void solve();

private:
    MatrixD matrix;
    double _infinity;
    double _record;

    double subtractFromMatrix(MatrixD& m) const;
    double getCoefficient(const MatrixD& m, size_t r, size_t c) const;
    std::list<std::pair<size_t, size_t>> findZerosWithMaxCoeff(const MatrixD& matrix) const;
    void handleMatrix(MatrixD matrix, std::list<std::pair<size_t, size_t>> path, double bottomLimit);
};

#endif // LITTLESOLVER_H