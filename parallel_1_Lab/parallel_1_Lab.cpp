#include <iostream>
#include <omp.h>
#include <thread>

using namespace std;

void show(int** mat, int row, int column) {

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "\n\n";
}


void show(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n\n";
}


int main() {
    setlocale(LC_ALL, "Russian");

    int column, row;
    int** matrix;
    int* array_;
    int* result;
    int id, n;

    cout << "Введите количество строк матрицы: ";
    cin >> row;

    cout << "Введите количество столбцов матрицы: ";
    cin >> column;
    cout << '\n';

    matrix = new int* [row];
    array_ = new int[column];
    result = new int[column];

    for (int i = 0; i < row; ++i) {
        matrix[i] = new int[column];
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }
    show(matrix, row, column);


    for (int i = 0; i < column; ++i) {
        array_[i] = rand() % 10;
    }
    show(array_, column);


    clock_t timeBegin = clock();

    for (int i = 0; i < row; ++i)
    {
        result[i] = 0;
        for (int j = 0; j < column; ++j)
        {
            result[i] += matrix[i][j] * array_[j];
        }
    }

    show(result, row);


#pragma omp parallel private(id) shared(matrix, array_, result)
    {
#pragma omp for schedule (dynamic)
        
        for (int i = 0; i < row; ++i) {
            result[i] = 0;
            for (int j = 0; j < column; ++j)
            {
                result[i] += matrix[i][j] * array_[j];
            }
        }
    }


    for (int i = 0; i < row; ++i) {
        delete[] matrix[i];
    }
    delete[] array_;
    delete[] result;

    system("pause");
    return 0;
}