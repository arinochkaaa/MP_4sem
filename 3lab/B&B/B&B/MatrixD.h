#pragma once
#ifndef MATRIXD_H
#define MATRIXD_H

#include <vector>
#include <stdexcept>
#include <limits>
#include <iostream>

class MatrixD {
public:
    // ����������� ��� �������� ������� ��������� �������
    MatrixD(size_t rows, size_t cols, double initialValue = 0.0);

    // ����������� ��� �������� ������� �� ������������ ������
    MatrixD(const std::vector<std::vector<double>>& inputData);

    // �������� ������� � ��������� �������
    double& operator()(size_t row, size_t col);

    // ����������� �������� ������� � ��������� �������
    double operator()(size_t row, size_t col) const;

    // ��������� ���������� �����
    size_t getRows() const;

    // ��������� ���������� ��������
    size_t getCols() const;

    // ��������� ������� ������� (�������������� ���������� �������)
    size_t size() const;

    // �������� ������ � �������
    void removeRowColumn(size_t row, size_t col);

    // ���������� ������������� �� ��������� �������
    void addInfinity(size_t row, size_t col);

    // ����� ������� (��� �������)
    void print() const;

    // ��������� ������� ������
    size_t rowIndex(size_t row) const;

    // ��������� ������� �������
    size_t columnIndex(size_t col) const;

private:
    std::vector<std::vector<double>> data; // ������ �������
    size_t rows; // ���������� �����
    size_t cols; // ���������� ��������
};

#endif // MATRIXD_H