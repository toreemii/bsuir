#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Student {
    string surname;
    string groupNumber;
    int physicsGrade;
    int mathGrade;
    int informaticsGrade;
};

void createFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file.close();
        cout << "Файл создан успешно.\n";
    }
    else {
        cout << "Ошибка при создании файла.\n";
    }
}

void addStudent(const string& filename) {
    string surname, groupNumber;
    int physicsGrade, mathGrade, informaticsGrade;
    cout << "Введите фамилию: ";
    cin >> surname;
    cout << "Введите номер группы: ";
    cin >> groupNumber;
    cout << "Введите оценку по физике: ";
    cin >> physicsGrade;
    cout << "Введите оценку по математике: ";
    cin >> mathGrade;
    cout << "Введите оценку по информатике: ";
    cin >> informaticsGrade;

    ofstream file(filename, ofstream::app);
    if (file.is_open()) {
        file << surname << " " << groupNumber << " "
            << physicsGrade << " " << mathGrade << " "
            << informaticsGrade << "\n";
        file.close();
        cout << "Студент добавлен успешно.\n";
    }
    else {
        cout << "Ошибка при добавлении студента.\n";
    }
}

void viewStudents(const string& filename) {
    ifstream file(filename);
    string surname, groupNumber;
    int physicsGrade, mathGrade, informaticsGrade;
    if (file.is_open()) {
        while (file >> surname >> groupNumber >> physicsGrade >> mathGrade >> informaticsGrade) {
            cout << surname << " " << groupNumber << " "
                << physicsGrade << " " << mathGrade << " "
                << informaticsGrade << "\n";
        }
        file.close();
    }
    else {
        cout << "Ошибка при чтении файла.\n";
    }
}

void findTopStudents(const string& filename) {
    ifstream file(filename);
    ofstream outFile("top_students.txt");
    string surname, groupNumber;
    int physicsGrade, mathGrade, informaticsGrade;

    if (file.is_open() && outFile.is_open()) {
        while (file >> surname >> groupNumber >> physicsGrade >> mathGrade >> informaticsGrade) {
            if (mathGrade >= 4 && informaticsGrade >= 4) {
                outFile << surname << " " << groupNumber << " "
                    << physicsGrade << " " << mathGrade << " "
                    << informaticsGrade << "\n";
            }
        }
        file.close();
        outFile.close();
        cout << "Результаты записаны в файл top_students.txt.\n";
    }
    else {
        cout << "Ошибка при чтении или записи файла.\n";
    }
}

void menu() {
    const string filename = "students.txt";
    int choice;

    do {
        cout << "Меню:\n";
        cout << "1. Создание файла\n";
        cout << "2. Просмотр записей\n";
        cout << "3. Добавление записи\n";
        cout << "4. Найти студентов с оценками не ниже 4 по информатике и математике\n";
        cout << "5. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createFile(filename);
            break;
        case 2:
            viewStudents(filename);
            break;
        case 3:
            addStudent(filename);
            break;
        case 4:
            findTopStudents(filename);
            break;
        case 5:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    } while (choice != 5);
}

int main() {
    setlocale(LC_ALL, "Ru");
    menu();
    return 0;
}
