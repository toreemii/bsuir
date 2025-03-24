# ЛАБОРАТОРНАЯ РАБОТА №2

## Цель работы
Реализовать программу, формирующую множество равное разности двух исходных множеств (без учёта кратных вхождений элементов).
Вариант - 4.

## Постановка задачи
Реализовать алгоритм разности.

## Ипользуемые понятия
- **Множество** — это любая определенная совокупность объектов. 
- Объекты, из которых составлено множество, называются его **элементами**. Элементы множества различны и отличны друг от друга.
- **Разность множеств** A и B — это множество, которое состоит из тех элементов, которые одновременно принадлежат множеству A и не принадлежат множеству B.
- **Разностью неориентированных множеств А и В без учёта кратных вхождений элементов** будем называть неориентированное множество Ѕ тогда и только тогда, когда для любого х истинно Ѕ|x| = max{min{A|x|, 1}-min{B|x|, 1}, 0}.

# Алгоритм
Чтобы вычислить разность для произвольного количества множеств, необходимо передать в функцию разности элементы всех этих множеств. Для этого сначала нужно прочитать все множества из файла (с проверкой их корректности), извлечь содержимое каждого множества, разделить каждое множество на отдельные элементы и затем передать эти элементы в функцию, которая будет вычислять разность.

---

# Разбор алгоритма кода на C++

## Чтение множества из файла

```cpp
void readFile(vector<string>& sets, ifstream& inputFile) {
    string line;
    while (!inputFile.eof()) {
        getline(inputFile, line);
        sets.push_back(line);
    }
    inputFile.close();
}
```

Функция `readFile` предназначена для чтения множества из файла. Она построчно считывает содержимое файла `inputFile` и добавляет строки в вектор `sets`.

---

## Вывод множеств в консоль

```cpp
void displaySets(vector<string> sets) {
    for (int i = 0; i <= sets.size(); i++) {
        if (i < sets.size()) {
            cout << "Множество " << i + 1 << " :" << endl;
            cout << "{" << sets[i] << "}" << endl;
        }
        else {
            cout << "Все множества записаны." << endl;
            cout << "----------------------" << endl;
        }
    }
}
```

Функция `displaySets` используется для вывода множества на экран. Она проходит по вектору `sets` и выводит каждое множество, оформляя его в фигурные скобки `{}`.

---

## Извлечение элементов множества

```cpp
vector<string> extractAndSortElements(const string& setString) {
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;

    for (char c : setString) {
        if (c == '{' && braceDepth == 0) {
            braceDepth++;
            currentElement += c;
        }
        else if (c == '}' && braceDepth > 0) {
            braceDepth--;
            currentElement += c;
            if (braceDepth == 0 && !currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
            if (c == '{') braceDepth++;
            else if (c == '}') braceDepth--;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(currentElement);
    }
    return elements;
}
```

Функция `extractAndSortElements` предназначена для обработки строкового представления множества. Она извлекает элементы, разделяя их запятыми и учитывая вложенность фигурных скобок.

---

## Разность множеств

```cpp
void differenceSets(vector<string>& sets, string& initialResult) {
    if (sets.size() == 0) return;

    vector<string> uniqueElements;
    vector<string> elementsA = extractAndSortElements(sets[0]);
    vector<string> elementsB = extractAndSortElements(sets[1]);
    int index = 0;
    for (const string& element : elementsA) {
        bool foundInB = false;
        for (const string& elementB : elementsB) {
            if (element == elementB) {
                foundInB = true;
                break;
            }
        }
        if (!foundInB) {
            uniqueElements.push_back(element);
        }
    }

    string finalResult;
    for (int i = 0; i < uniqueElements.size(); i++) {
        finalResult += uniqueElements[i];
        if (i < uniqueElements.size() - 1) {
            finalResult += ",";
        }
    }

    cout << "Результат разности:" << endl;
    cout << "{" << finalResult << "}" << endl;
    initialResult = "{" + finalResult + "}";
}
```

Функция `differenceSets` вычисляет разность двух множеств. Она принимает на вход вектор `sets`, извлекает элементы первого и второго множества, а затем удаляет элементы второго множества из первого.

---

## Главная функция программы

```cpp
int main() {
    setlocale(LC_ALL, "RU");
    string differenceResult, fileName;
    vector<string> sets;

    int kod;
    while (true) {
        cout << "Открыть файл - 1." << endl;
        cout << "Вывести множества - 2." << endl;
        cout << "Найти разность множеств - 3." << endl;
        cin >> kod;
        switch (kod) {
        case 1: {
            ifstream inputFile("C:\\Users\\user\\Desktop\\пиоивис2\\mn.txt.txt");
            if (inputFile.is_open()) {
                cout << "Файл открыт успешно!" << endl;
                cout << "--------------------" << endl;
                readFile(sets, inputFile);
            }
            else {
                cout << "Ошибка открытия файла." << endl;
            }
            break;
        }
        case 2:
            displaySets(sets);
            break;
        case 3:
            differenceSets(sets, differenceResult);
            exit(0);
            break;
        }
    }
    return 0;
}
```

В `main` реализован основной цикл программы, в котором пользователь может выбрать действие:
- Открыть файл и считать множества,
- Вывести множества в консоль,
- Найти разность двух первых множеств.

Программа работает в бесконечном цикле, пока пользователь не выберет операцию нахождения разности, после чего выполнение завершается.

---

## Пример работы кода
   <img src="" width="400" />

   <img src="" width="400" />

   <img src="" width="400" />

## Вывод
В ходе лабораторной работы была реализована программа разности двух множеств без учета кратных вхождений элементов.

## Использованная литература
В ходе лабораторной работы никакие источники не были использованы.

