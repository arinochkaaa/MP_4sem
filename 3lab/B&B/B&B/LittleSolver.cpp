#include "LittleSolver.h"

// Конструктор
LittleSolver::LittleSolver(const MatrixD& initialMatrix)
    : matrix(initialMatrix), _infinity(std::numeric_limits<double>::infinity()), _record(std::numeric_limits<double>::max()) {}

// Основной метод для запуска алгоритма
void LittleSolver::solve() {
    handleMatrix(matrix, {}, 0);
}

// Вычитание минимальных элементов из строк и столбцов
double LittleSolver::subtractFromMatrix(MatrixD& m) const {
    double subtractSum = 0;
    std::vector<double> minRow(m.size(), std::numeric_limits<double>::max()),
        minColumn(m.size(), std::numeric_limits<double>::max());

    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j)
            if (m(i, j) < minRow[i])
                minRow[i] = m(i, j);

        for (size_t j = 0; j < m.size(); ++j) {
            if (m(i, j) < _infinity) {
                m(i, j) -= minRow[i];
            }
            if ((m(i, j) < minColumn[j]))
                minColumn[j] = m(i, j);
        }
    }

    for (size_t j = 0; j < m.size(); ++j)
        for (size_t i = 0; i < m.size(); ++i)
            if (m(i, j) < _infinity) {
                m(i, j) -= minColumn[j];
            }

    for (auto i : minRow)
        subtractSum += i;

    for (auto i : minColumn)
        subtractSum += i;

    return subtractSum;
}

// Расчет коэффициента для нулевого элемента
double LittleSolver::getCoefficient(const MatrixD& m, size_t r, size_t c) const {
    double rmin, cmin;
    rmin = cmin = std::numeric_limits<double>::max();

    for (size_t i = 0; i < m.size(); ++i) {
        if (i != r)
            rmin = std::min(rmin, m(i, c));
        if (i != c)
            cmin = std::min(cmin, m(r, i));
    }

    return rmin + cmin;
}

// Поиск нулевых элементов с максимальными коэффициентами
std::list<std::pair<size_t, size_t>> LittleSolver::findZerosWithMaxCoeff(const MatrixD& matrix) const {
    std::list<std::pair<size_t, size_t>> zeros;
    std::list<double> coeffList;
    double maxCoeff = 0;

    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < matrix.size(); ++j)
            if (!matrix(i, j)) {
                zeros.emplace_back(i, j);
                coeffList.push_back(getCoefficient(matrix, i, j));
                maxCoeff = std::max(maxCoeff, coeffList.back());
            }

    auto zIter = zeros.begin();
    auto cIter = coeffList.begin();
    while (zIter != zeros.end()) {
        if (*cIter != maxCoeff) {
            zIter = zeros.erase(zIter);
            cIter = coeffList.erase(cIter);
        }
        else {
            ++zIter;
            ++cIter;
        }
    }

    return zeros;
}

// Обработка матрицы (рекурсивный метод)
void LittleSolver::handleMatrix(MatrixD matrix, std::list<std::pair<size_t, size_t>> path, double bottomLimit) {
    bottomLimit += subtractFromMatrix(matrix);

    if (bottomLimit > _record) {
        return;
    }

    auto zeros = findZerosWithMaxCoeff(matrix);

    if (zeros.empty()) {
        if (bottomLimit < _record) {
            _record = bottomLimit;
            // Сохранение пути как решения
        }
        return;
    }

    auto edge = zeros.front();
    auto newMatrix(matrix);
    newMatrix.removeRowColumn(edge.first, edge.second);
    auto newPath(path);
    newPath.emplace_back(matrix.rowIndex(edge.first), matrix.columnIndex(edge.second));
    newMatrix.addInfinity(edge.first, edge.second);
    handleMatrix(newMatrix, newPath, bottomLimit);

    newMatrix = matrix;
    newMatrix(edge.first, edge.second) = _infinity + 1;
    handleMatrix(newMatrix, path, bottomLimit);
}