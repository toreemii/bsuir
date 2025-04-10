#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Flight {
    string naznachenie;
    int flightNumber;
    string time;
};

struct hashNode {
    Flight data;
    bool occupied;
};

int hash1(int key, int size) {
    return key % size;
}

int hash2(int key, int size) {
    return 1 + (key % (size - 2));
}

void AddToHashTable(hashNode* table, int size, Flight flight) {
    int i = hash1(flight.flightNumber, size);
    int c = hash2(flight.flightNumber, size);

    while (table[i].occupied) {
        i = (i - c) % size;
        if (i < 0)i += size;
    }
    table[i].data = flight;
    table[i].occupied = true;
}

int searchInHashTable(hashNode* table, int size, int key) {
    int i = hash1(key, size);
    int c = hash2(key, size);
    int firstIndex = i;

    while (table[i].occupied) {
        if (table[i].data.flightNumber == key) {
            return i;
        }
        i = (i - c) % size;
        if (i < 0) i += size;
        if (i == firstIndex) break;
    }
    return -1;
}

void HashTable(hashNode* table, int size) {
    cout << "\nХеш-таблица:\n";
    for (int i = 0; i < size; i++) {
        cout << "H[" << i << "] = ";
        if (table[i].occupied) {
            cout << "Номер рейса: " << table[i].data.flightNumber
                << ", Пункт: " << table[i].data.naznachenie
                << ", Время: " << table[i].data.time;
        }
        else {
            cout << "пусто";
        }
        cout << endl;
    }
}

void Array(Flight* arr, int size) {
    cout << "\nИсходный массив:\n";
    for (int i = 0; i < size; i++) {
        cout << "Элемент " << i << ": Номер рейса: " << arr[i].flightNumber
            << ", Пункт: " << arr[i].naznachenie
            << ", Время: " << arr[i].time << endl;
    }
}

void inputFlights(Flight* arr, int size) {
    cout << "Введите данные для " << size << " рейсов:\n";
    for (int i = 0; i < size; i++) {
        cout << "\nРейс " << i + 1 << ":\n";
        cout << "Пункт назначения: ";
        cin.ignore(cin.rdbuf()->in_avail());
        getline(cin, arr[i].naznachenie);

        cout << "Номер рейса: ";
        cin >> arr[i].flightNumber;

        cout << "Время отправления (в формате ЧЧ:ММ): ";
        cin.ignore(cin.rdbuf()->in_avail());
        getline(cin, arr[i].time);
    }
}


int main() {
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    const int n = 7;
    const int m = 10;

    Flight flights[n];
    inputFlights(flights, n);

    hashNode* hashTable = new hashNode[m];
    for (int i = 0; i < m; i++) {
        hashTable[i].occupied = false;
    }

    for (int i = 0; i < n; i++) {
        AddToHashTable(hashTable, m, flights[i]);
    }

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Вывести исходный массив\n";
        cout << "2. Вывести хеш-таблицу\n";
        cout << "3. Найти элемент по номеру рейса\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        switch (choice) {
        case 1:
            Array(flights, n);
            break;
        case 2:
            HashTable(hashTable, m);
            break;
        case 3: {
            int searchKey;
            cout << "Введите номер рейса для поиска: ";
            cin >> searchKey;
            int index = searchInHashTable(hashTable, m, searchKey);
            if (index != -1) {
                cout << "Найден элемент:\n";
                cout << "Номер рейса: " << hashTable[index].data.flightNumber
                    << ", Пункт: " << hashTable[index].data.naznachenie
                    << ", Время: " << hashTable[index].data.time << endl;
            }
            else {
                cout << "Элемент с номером рейса " << searchKey << " не найден\n";
            }
            break;
        }
        case 0:
            cout << "bye bye!\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    delete[] hashTable;
    return 0;
}
