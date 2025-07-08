#include "MatrixD.h"
#include "LittleSolver.h"

int main() {
    MatrixD mat(3, 3, 1.0); // Создаем матрицу 3x3, заполненную единицами
    mat(1, 1) = 5.0;       // Изменяем элемент в центре
    mat.print();            // Выводим матрицу

    LittleSolver solver(mat);
    solver.solve(); // Запускаем алгоритм Литтла

    return 0;
}