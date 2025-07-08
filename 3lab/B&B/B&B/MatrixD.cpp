#include <vector>
#include <stdexcept>
#include <limits>
#include <iostream>

class MatrixD {
public:
    // Конструктор для создания матрицы заданного размера
    MatrixD(size_t rows, size_t cols, double initialValue = 0.0)
        : data(rows, std::vector<double>(cols, initialValue)), rows(rows), cols(cols) {}

    // Конструктор для создания матрицы из существующих данных
    MatrixD(const std::vector<std::vector<double>>& inputData)
        : data(inputData), rows(inputData.size()), cols(inputData.empty() ? 0 : inputData[0].size()) {}

    // Оператор доступа к элементам матрицы
    double& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    // Константный оператор доступа к элементам матрицы
    double operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    // Получение количества строк
    size_t getRows() const {
        return rows;
    }

    // Получение количества столбцов
    size_t getCols() const {
        return cols;
    }

    // Получение размера матрицы (предполагается квадратная матрица)
    size_t size() const {
        if (rows != cols) {
            throw std::logic_error("Matrix is not square");
        }
        return rows;
    }

    // Удаление строки и столбца
    void removeRowColumn(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }

        // Удаление строки
        data.erase(data.begin() + row);
        --rows;

        // Удаление столбца
        for (auto& r : data) {
            r.erase(r.begin() + col);
        }
        --cols;
    }

    // Добавление бесконечности на указанную позицию
    void addInfinity(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        data[row][col] = std::numeric_limits<double>::infinity();
    }

    // Вывод матрицы (для отладки)
    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    // Получение индекса строки (если требуется)
    size_t rowIndex(size_t row) const {
        return row;
    }

    // Получение индекса столбца (если требуется)
    size_t columnIndex(size_t col) const {
        return col;
    }

private:
    std::vector<std::vector<double>> data; // Данные матрицы
    size_t rows; // Количество строк
    size_t cols; // Количество столбцов
};