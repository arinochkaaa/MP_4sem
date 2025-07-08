#pragma once
#ifndef MATRIXD_H
#define MATRIXD_H

#include <vector>
#include <stdexcept>
#include <limits>
#include <iostream>

class MatrixD {
public:
    // Конструктор для создания матрицы заданного размера
    MatrixD(size_t rows, size_t cols, double initialValue = 0.0);

    // Конструктор для создания матрицы из существующих данных
    MatrixD(const std::vector<std::vector<double>>& inputData);

    // Оператор доступа к элементам матрицы
    double& operator()(size_t row, size_t col);

    // Константный оператор доступа к элементам матрицы
    double operator()(size_t row, size_t col) const;

    // Получение количества строк
    size_t getRows() const;

    // Получение количества столбцов
    size_t getCols() const;

    // Получение размера матрицы (предполагается квадратная матрица)
    size_t size() const;

    // Удаление строки и столбца
    void removeRowColumn(size_t row, size_t col);

    // Добавление бесконечности на указанную позицию
    void addInfinity(size_t row, size_t col);

    // Вывод матрицы (для отладки)
    void print() const;

    // Получение индекса строки
    size_t rowIndex(size_t row) const;

    // Получение индекса столбца
    size_t columnIndex(size_t col) const;

private:
    std::vector<std::vector<double>> data; // Данные матрицы
    size_t rows; // Количество строк
    size_t cols; // Количество столбцов
};

#endif // MATRIXD_H