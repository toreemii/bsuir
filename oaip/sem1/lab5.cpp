#include <iostream>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Ru");

    int n;
    cout << "Введите длину n: ";
    cin >> n;
    int** matrix = new int* [n];

    cout << "Введите матрицу: " << endl;
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }

    int sum = 0;
    for (int i = 0; i < n; i += 2)
    {
        int m = matrix[i][0];
        for (int j = 0; j < n; j++)
        {
                m = min(matrix[i][j], m);
        }
        sum += m;
    }

    for (int i = 1; i < n; i += 2)
    {
        int m = matrix[i][0];
        for (int j = 0; j < n; j++)
        {
                m = max(matrix[i][j], m);
        }
        sum += m;
    }
    cout << "Результат: "<< sum;

    delete[] matrix;
}

