#include <vector>
#include <stdexcept>
#include <limits>
#include <iostream>

class MatrixD {
public:
    // ����������� ��� �������� ������� ��������� �������
    MatrixD(size_t rows, size_t cols, double initialValue = 0.0)
        : data(rows, std::vector<double>(cols, initialValue)), rows(rows), cols(cols) {}

    // ����������� ��� �������� ������� �� ������������ ������
    MatrixD(const std::vector<std::vector<double>>& inputData)
        : data(inputData), rows(inputData.size()), cols(inputData.empty() ? 0 : inputData[0].size()) {}

    // �������� ������� � ��������� �������
    double& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    // ����������� �������� ������� � ��������� �������
    double operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        return data[row][col];
    }

    // ��������� ���������� �����
    size_t getRows() const {
        return rows;
    }

    // ��������� ���������� ��������
    size_t getCols() const {
        return cols;
    }

    // ��������� ������� ������� (�������������� ���������� �������)
    size_t size() const {
        if (rows != cols) {
            throw std::logic_error("Matrix is not square");
        }
        return rows;
    }

    // �������� ������ � �������
    void removeRowColumn(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }

        // �������� ������
        data.erase(data.begin() + row);
        --rows;

        // �������� �������
        for (auto& r : data) {
            r.erase(r.begin() + col);
        }
        --cols;
    }

    // ���������� ������������� �� ��������� �������
    void addInfinity(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("Matrix indices out of range");
        }
        data[row][col] = std::numeric_limits<double>::infinity();
    }

    // ����� ������� (��� �������)
    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    // ��������� ������� ������ (���� ���������)
    size_t rowIndex(size_t row) const {
        return row;
    }

    // ��������� ������� ������� (���� ���������)
    size_t columnIndex(size_t col) const {
        return col;
    }

private:
    std::vector<std::vector<double>> data; // ������ �������
    size_t rows; // ���������� �����
    size_t cols; // ���������� ��������
};