#include <iostream>  
#include <cmath>     // Библиотека для работы с математическими функциями

using namespace std;

double M_PI = 3.14159265358979323846;

// Определяем функцию для вычисления суммы S(x)
double S(double x, int n) {
    double sum = 0;  // Создаём переменную для хранения суммы 
    for (int k = 1; k <= n; ++k) {  
        sum += pow(x, k) * cos(k * M_PI / 3) / k;  // Вычисляем и добавляем каждый элемент ряда в сумму
    }
    return sum;  
}

// Определяем функцию для вычисления Y(x)
double Y(double x) {
    return -0.5 * log(1 - 2 * x * cos(M_PI / 3) + x * x);
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    double x;  // Переменная для хранения значения x
    cout << "Введите значение x: "; 
    cin >> x; 

    double epsilon;  // Переменная для хранения значения точности epsilon
    cout << "Введите значение точности epsilon (например, 0.001): ";  
    cin >> epsilon;  

    int n = 1;  // Начальное значение для итераций (n)
    double Sx = 0, Yx = Y(x);  // Инициализация суммы S(x) и функции Y(x)

    // Цикл, который выполняется до тех пор, пока разница между S(x) и Y(x) больше epsilon
    do {
        Sx = S(x, n);  // Вычисляем сумму S(x) для текущего n
        ++n;  // Увеличиваем n на 1 (переходим к следующему шагу)
    } while (fabs(Sx - Yx) >= epsilon);  // Условие выхода из цикла: |S(x) - Y(x)| < epsilon

    // Выводим результат
    cout << "Требуемая точность достигнута на шаге n = " << n <<endl;
    cout << "S(x) = " << Sx << endl;
    cout << "Y(x) = " << Yx << endl;

    return 0;  
}
