#include <iostream>
#include <vector>

using namespace std;

vector<int> U = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

vector<int> union_sets( vector<int> X, vector<int> Y) { 
    vector<int> result = X; 
    for (int y : Y) {
        bool found = false; // Переменная для проверки, есть ли элемент y в X
        // Проверяем, содержится ли y в result 
        for (int r : result) {
            if (r == y) {
                found = true; 
                break; 
            }
        }
        // Если элемент y не был найден в result, добавляем его
        if (!found) {
            result.push_back(y);
        }
    }
    return result; // Придаём функции значение объединения
}

vector<int> intersection_sets(vector<int> X, vector<int> Y) { 
    vector<int> result; // пустой вектор для хранения результата
    for (int x : X) {
        for (int y : Y) {
            if (x == y) {
                result.push_back(x); 
                break; 
            }
        }
    }
    return result; 
}

vector<int> difference_sets( vector<int> X, vector<int> Y) {
    vector<int> result; 
    for (int x : X) {
        bool found = false; 
        for (int y : Y) {
            if (x == y) {
                found = true; 
                break; 
            }
        }
        if (!found) {
            result.push_back(x);
        }
    }
    return result; 
}

vector<int> symmetric_difference_sets(vector<int> X, vector<int> Y) {
    vector<int> result; 
    for (int x : X) {
        bool found = false; 
        for (int y : Y) {
            if (x == y) {
                found = true; 
                break; 
            }
        }
        if (!found) {
            result.push_back(x);
        }
    }
    for (int y : Y) {
        bool found = false; 
        for (int x : X) {
            if (x == y) {
                found = true; 
                break; 
            }
        }
        if (!found) {
            result.push_back(y);
        }
    }
    return result; 
}

vector<int> complement_set( vector<int> U, vector<int> X) {
    vector<int> result; 
    for (int u : U) {
        bool found = false; 
        for (int x : X) {
            if (u == x) {
                found = true; 
                break; 
            }
        }
      
        if (!found) {
            result.push_back(u);
        }
    }
    return result; 
}


// Функция для вывода вектора
void print_console( vector<int> vec) {
    for (int i : vec) {
        cout << i << " "; 
    }
    cout << endl; 
}

// Функция для ввода множества с проверкой
vector<int> input_set(int size) {
    vector<int> set; 
    for (int i = 0; i < size; ++i) {
        int element;
        while (true) {
            cin >> element;
            if (element >= 1 && element <= 10) {
                bool is_duplicate = false;
                for (int existing_element : set) {
                    if (existing_element == element) {
                        is_duplicate = true;
                        break;
                    }
                }
                if (is_duplicate) {
                    cout << "Элемент уже существует в множестве. Введите друнгой элемент: ";
                }
                else {
                    set.push_back(element);
                    break;
                }
            }
            else {
                cout << "Неправильный ввод! Элемент должен быть натуральным числом от 1 до 10. Попробуйте снова: "; 
            }
        }
    }
    return set;
}

// Функция для ввода мощности множества с проверкой
int input_size() {
    int size;
    while (true) {
        cin >> size;
        if (size >= 1 && size <= 10) {
            break;
        }
        else {
            cout << "Неправильный ввод! Мощность множества должна быть от 1 до 10. Попробуйте снова." << endl; 
        }
    }
    return size;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Задано универсально множество U = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }" << endl;

    cout << "Введите мощность множества X (от 1 до 10): ";
    int size_X = input_size(); 
    cout << "Введите элементы множества X (натуральные числа от 1 до 10): ";
    vector<int> X = input_set(size_X); 

    cout << "Введите мощность множества Y (от 1 до 10): ";
    int size_Y = input_size(); 
    cout << "Введите элементы множества Y (натуральные числа от 1 до 10): ";
    vector<int> Y = input_set(size_Y); 

    // Вывод результатов
    cout << "Объединение: ";
    print_console(union_sets(X, Y));

    cout << "Пересечение: ";
    print_console(intersection_sets(X, Y));

    cout << "Разность (X - Y): ";
    print_console(difference_sets(X, Y));

    cout << "Разность (Y - X): ";
    print_console(difference_sets(Y, X));

    cout << "Симметрическая разность: ";
    print_console(symmetric_difference_sets(X, Y));

    cout << "Дополнение множества X относительно U: ";
    print_console(complement_set(U, X));

    cout << "Дополнение множества Y относительно U: ";
    print_console(complement_set(U, Y));

    return 0;
}
