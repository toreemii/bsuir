#include <iostream>
#include <vector>
using namespace std;

typedef vector<pair<int, int>> Graph;

// Инверсия графика: меняем местами компоненты в каждом кортеже
Graph inverse(const Graph& graph) {
    Graph inverted;
    for (auto& p : graph) {
        inverted.emplace_back(p.second, p.first);
    }
    return inverted;
}

// Композиция графиков: если конец одного кортежа совпадает с началом другого
Graph compose(const Graph& g1, const Graph& g2) {
    Graph result;
    for (auto& p1 : g1) {
        for (auto& p2 : g2) {
            if (p1.second == p2.first) {
                pair<int, int> composed_pair = make_pair(p1.first, p2.second);

                // Проверка на уникальность пары в result
                bool is_duplicate = false;
                for (auto& existing_pair : result) {
                    if (existing_pair == composed_pair) {
                        is_duplicate = true;
                        break;
                    }
                }

                // Добавляем только уникальные пары
                if (!is_duplicate) {
                    result.emplace_back(composed_pair);
                }
            }
        }
    }
    return result;
}

// Функция для проекции на заданную ось
vector<int> project(const Graph& graph, int axis) {
    vector<int> projection;
    for (auto& p : graph) {
        if (axis == 1) {
            if (projection.size() == 0) {
                projection.push_back(p.first);  // Проекция на первую компоненту
            }
            else {
                for (auto i : projection) {
                    if (i == p.first) {
                        break;
                    }
                    else if (i == *(projection.end() - 1)) {
                        projection.push_back(p.first);
                    }
                }
            }

        }
        else if (axis == 2) {
            if (projection.size() == 0) {
                projection.push_back(p.second);  // Проекция на первую компоненту
            }
            else {
                for (auto i : projection) {
                    if (i == p.second) {
                        break;
                    }
                    else if (i == *(projection.end() - 1)) {
                        projection.push_back(p.second);
                    }
                }
            }
        }
    }
    return projection;
    }
    

// Вывод графика
void printGraph(const Graph& graph) {
    if (graph.empty()) {
        cout << "∅";
    }
    else {
        for (auto& p : graph) {
            cout << "<" << p.first << ", " << p.second << "> ";
        }
    }
    cout << endl;
}

// Вывод результата проекции в формате <число1, число2, ...>
void printProjection(const vector<int>& projection) {
    if (projection.empty()) {
        cout << "Проекции нет";
    }
    else {
        cout << "<";
        for (size_t i = 0; i < projection.size(); ++i) {
            cout << projection[i];
            if (i != projection.size() - 1) {
                cout << ", ";
            }
        }
        cout << ">";
    }
    cout << endl;
}

// Функция для создания множества на основе выражения
vector<int> createSetFromExpression(int choice, int count) {
    vector<int> set;
    for (int k = 1; k <= count; ++k) {
        int element;
        switch (choice) {
        case 1: element = 3 * k + 2; break; // 3k + 2
        case 2: element = k * k; break;     // k^2
        case 3: element = 2 * k - 1; break; // 2k -1
        default:
            cout << "Некорректный выбор выражения. Элемент не добавлен.\n";
            continue;
        }
        set.push_back(element);
    }
    return set;
}

// Вывод множества
void printSet(const vector<int>& set) {
    if (set.empty()) {
        cout << "∅";
    }
    else {
        cout << "{ ";
        for (auto& elem : set) {
            cout << elem << " ";
        }
        cout << "}";
    }
    cout << endl;
}

// Декартово произведение множеств A и B
vector<pair<int, int>> cartesianProduct(const vector<int>& setA, const vector<int>& setB) {
    vector<pair<int, int>> result;
    for (auto a : setA) {
        for (auto b : setB) {
            result.emplace_back(a, b);
        }
    }
    return result;
}

// Вывод декартова произведения
void printCartesianProduct(const vector<pair<int, int>>& cartProduct) {
    if (cartProduct.empty()) {
        cout << "Нет декартово произведения";
    }
    else {
        for (auto& p : cartProduct) {
            cout << "<" << p.first << ", " << p.second << "> ";
        }
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Rus");

    Graph P, Q;
    int nP, nQ;

    // Универсальное множество U
    vector<int> universalSet;
    for (int i = 1; i <= 50; ++i) {
        universalSet.push_back(i);
    }

    // Ввод графика P вручную
    do {
        cout << "Введите количество пар в графике P (от 1 до 10): ";
        cin >> nP;
        cin.ignore();
    } while (nP < 1 || nP > 10);

    cout << "Введите пары (x y) для графика P:" << endl;
    for (int i = 0; i < nP; ++i) {
        int x, y;
        do {
            cin >> x >> y;
            if (x < 1 || x > 10 || y < 1 || y > 10) {
                cout << "Некорректный ввод. Числа должны быть в диапазоне от 1 до 10. Попробуйте снова: ";
            }
        } while (x < 1 || x > 10 || y < 1 || y > 10);

        // Проверка на наличие повторяющихся пар
        for (const auto& pair : P) {
            if (pair.first == x && pair.second == y) {
                cout << "Ошибка: повторяющаяся пара (" << x << ", " << y << ")" << endl;
                return 1;
            }
        }

        P.emplace_back(x, y);
    }

    // Ввод графика Q вручную
    do {
        cout << "Введите количество пар в графике Q (от 1 до 10): ";
        cin >> nQ;
        cin.ignore();
    } while (nQ < 1 || nQ > 10);

    cout << "Введите пары (x y) для графика Q:" << endl;
    for (int i = 0; i < nQ; ++i) {
        int x, y;
        do {
            cin >> x >> y;
            if (x < 1 || x > 10 || y < 1 || y > 10) {
                cout << "Некорректный ввод. Числа должны быть в диапазоне от 1 до 10. Попробуйте снова: ";
            }
        } while (x < 1 || x > 10 || y < 1 || y > 10);

        // Проверка на наличие повторяющихся пар
        for (const auto& pair : Q) {
            if (pair.first == x && pair.second == y) {
                cout << "Ошибка: повторяющаяся пара (" << x << ", " << y << ")" << endl;
                return 1;
            }
        }

        Q.emplace_back(x, y);
    }

    // Вывод графика P после ввода
    cout << "Введённый график P: ";
    printGraph(P);

    // Вывод графика Q после ввода
    cout << "Введённый график Q: ";
    printGraph(Q);

    // Ввод множества A с выбором способа ввода
    int nA, inputChoiceA;
    vector<int> setA;

    cout << "Выберите способ ввода для множества A:\n1 - Ввод вручную\n2 - Генерация по выражению\nВаш выбор: ";
    cin >> inputChoiceA;

    if (inputChoiceA == 1) {
        // Ввод множества A вручную
        do {
            cout << "Введите количество элементов в множестве A (от 1 до 10): ";
            cin >> nA;
        } while (nA < 1 || nA > 10);

        cout << "Введите элементы множества А: ";
        for (int i = 0; i < nA; ++i) {
            int elem;
            bool isDuplicate;
            do {
                isDuplicate = false;
                cin >> elem;

                // Проверяем, есть ли уже элемент в setA
                for (int existingElem : setA) {
                    if (existingElem == elem) {
                        isDuplicate = true;
                        cout << "В множестве повторяющиеся элементы!";
                        return 1;
                    }
                }
            } while (isDuplicate);

            setA.push_back(elem); // Добавляем элемент в множество
        }
    }
    else if (inputChoiceA == 2) {
        // Ввод множества A с помощью выражения
        int expressionChoiceA;
        do {
            cout << "Введите количество элементов в множестве A (от 1 до 10): ";
            cin >> nA;
        } while (nA < 1 || nA > 10);

        cout << "Выберите выражение для множества A:\n1 - 3k+2\n2 - k^2\n3 - 2k-1\nВаш выбор: ";
        cin >> expressionChoiceA;
        setA = createSetFromExpression(expressionChoiceA, nA);
    }
    else {
        cout << "Некорректный выбор способа ввода для множества A." << endl;
        return 1;
    }

    // Ввод множества B с выбором способа ввода
    int nB, inputChoiceB;
    vector<int> setB;

    cout << "Выберите способ ввода для множества B:\n1 - Ввод вручную\n2 - Генерация по выражению\nВаш выбор: ";
    cin >> inputChoiceB;

    if (inputChoiceB == 1) {
        // Ввод множества B вручную
        do {
            cout << "Введите количество элементов в множестве B (от 1 до 10): ";
            cin >> nB;
        } while (nB < 1 || nB > 10);

        cout << "Введите элементы множества B: ";
        for (int i = 0; i < nB; ++i) {
            int elem;
            bool isDuplicate;
            do {
                isDuplicate = false;
                cin >> elem;

                // Проверяем, есть ли уже элемент в setB
                for (int existingElem : setB) {
                    if (existingElem == elem) {
                        isDuplicate = true;
                        cout << "В множестве повторяющиеся элементы!";
                        return 1;
                    }
                }
            } while (isDuplicate);

            setB.push_back(elem); // Добавляем элемент в множество
        }
    }
    else if (inputChoiceB == 2) {
        // Ввод множества B с помощью выражения
        int expressionChoiceB;
        do {
            cout << "Введите количество элементов в множестве B (от 1 до 10): ";
            cin >> nB;
        } while (nB < 1 || nB > 10);

        cout << "Выберите выражение для множества B:\n1 - 3k+2\n2 - k^2\n3 - 2k-1\nВаш выбор: ";
        cin >> expressionChoiceB;
        setB = createSetFromExpression(expressionChoiceB, nB);
    }
    else {
        cout << "Некорректный выбор способа ввода для множества B." << endl;
        return 1;
    }

    // Вывод множеств A и B
    cout << "Множество A: ";
    printSet(setA);
    cout << "Множество B: ";
    printSet(setB);

    // Остальная часть кода
    // Инверсия и композиция графиков
    cout << "Инверсия графика P: ";
    printGraph(inverse(P));

    cout << "Инверсия графика Q: ";
    printGraph(inverse(Q));

    // Композиция графиков P и Q
    cout << "Композиция графиков P и Q: ";
    Graph R = compose(P, Q);
    if (R.empty()) {
        cout << "Композиция данных графиков отсутствует!" << endl;
    }
    else {
        printGraph(R);
    }

    // Декартово произведение
    cout << "Декартово произведение A и B: ";
    printCartesianProduct(cartesianProduct(setA, setB));

    // Проекции графиков P и Q
    int axis;
    cout << "Выберите ось для проекции графика P (1 - первая ось, 2 - вторая ось): ";
    cin >> axis;
    vector<int> proj_P = project(P, axis);
    cout << "Проекция графика P на ось " << axis << ":" << endl;
    printProjection(proj_P);

    cout << "Выберите ось для проекции графика Q (1 - первая ось, 2 - вторая ось): ";
    cin >> axis;
    vector<int> proj_Q = project(Q, axis);
    cout << "Проекция графика Q на ось " << axis << ":" << endl;
    printProjection(proj_Q);

    return 0;
}

