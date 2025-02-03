#include <iostream>
#include <math.h>
using namespace std;

double find_root(double);
double find_root_r(double, double);

int main()
{
    setlocale(LC_ALL, "ru");
    double a;
    cout << "Введите а: ";
    cin >> a;
    if (a <= 0)
    {
        cout << "Ошибка: число меньше нуля или равно нулю.";
        return 0;
    }
    cout << "Корень из числа а через обычную функцию: " << find_root(a);
    cout << "\nКорень из числа а через реккурентную функцию: " << find_root_r(0.5 * (1 + a), a);
    return 0;
}

double find_root(double a)
{
    double r = 0.5 * (1 + a);
    while (abs(r * r - a) > 0.01)
    {
        r = 0.5 * (r + a / r);
        cout << r << endl;
    }

    return r;
}

double find_root_r(double r, double a)
{
    double new_r = 0.5 * (r + a / r);
    cout << r << endl;
    if (abs(new_r - r) < 0.01)
    {
        return new_r;
    }
    return find_root_r(new_r, a);
}

