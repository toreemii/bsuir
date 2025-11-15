#include <iostream>  
#include <cmath>     

using namespace std;

double M_PI = 3.14159265358979323846;

double S(double x, int n) {
    double sum = 0;   
    for (int k = 1; k <= n; ++k) {  
        sum += pow(x, k) * cos(k * M_PI / 3) / k;  // Вычисляем и добавляем каждый элемент ряда в сумму
    }
    return sum;  
}

double Y(double x) {
    return -0.5 * log(1 - 2 * x * cos(M_PI / 3) + x * x);
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    double x;  
    cout << "Введите значение x: "; 
    cin >> x; 

    double epsilon;  
    cout << "Введите значение точности epsilon (например, 0.001): ";  
    cin >> epsilon;  

    int n = 1;  
    double Sx = 0, Yx = Y(x);  

    do {
        Sx = S(x, n);  
        ++n;  
    } while (fabs(Sx - Yx) >= epsilon);  

    cout << "Требуемая точность достигнута на шаге n = " << n <<endl;
    cout << "S(x) = " << Sx << endl;
    cout << "Y(x) = " << Yx << endl;

    return 0;  
}
