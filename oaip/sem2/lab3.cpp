#include <iostream>
using namespace std;

struct Spis2 {
    int info;
    Spis2* next;
    Spis2* prev;
};

Spis2* start = NULL, * ennd = NULL;

void Create_Spis2(Spis2** b, Spis2** e, int in) {
    Spis2* t = new Spis2;
    t->info = in;
    t->next = t->prev = NULL;
    *b = *e = t;
}

void Add_Spis2(int kod, Spis2** b, Spis2** e, int in) {
    if (*b == NULL) {
        Create_Spis2(b, e, in);
        return;
    }
    Spis2* t = new Spis2;
    t->info = in;
    if (kod == 0) { 
        t->prev = NULL;
        t->next = *b;
        (*b)->prev = t;
        *b = t;
    }
    else { 
        t->next = NULL;
        t->prev = *e;
        (*e)->next = t;
        *e = t;
    }
}

void View_Spis2(int kod, Spis2* t) {
    while (t != NULL) {
        cout << t->info << " ";
        if (kod == 0) t = t->next;
        else t = t->prev;
    }
    cout << endl;
}

void Del_All(Spis2** b, Spis2** e) {
    Spis2* t;
    while (*b != NULL) {
        t = *b;
        *b = (*b)->next;
        delete t;
    }
    *e = NULL;
    cout << "Список очищен." << endl;
}

void perem(Spis2** oldstart, Spis2** oldend, Spis2** newstart, Spis2** newend) {
    if (*oldstart == NULL) {
        cout << "Список пуст!" << endl;
        return;
    }

    Spis2* maxNode = *oldstart;
    Spis2* current = *oldstart;

    while (current != NULL) {
        if (current->info > maxNode->info) {
            maxNode = current;
        }
        current = current->next;
    }

    if (maxNode == *oldstart) {
        cout << "Нет элементов между вершиной и максимумом!" << endl;
        return;
    }

    current = (*oldstart)->next;  
    while (current != maxNode) {
        Spis2* next = current->next;  

        Add_Spis2(1, newstart, newend, current->info);

        if (current->prev)
            current->prev->next = current->next;
        if (current->next)
            current->next->prev = current->prev;

        delete current;
        current = next;
    }

    cout << "Элементы перенесены!" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    int in, kod, kod1;
    Spis2* newstart = NULL, * newend = NULL;

    while (true) {
        cout << "\nМеню:\n\t1 - Создать список\n\t2 - Добавить элемент\n\t3 - Просмотреть список\n\t4 - Удалить список\n\t5 - Перенести элементы\n\t0 - Выход\nВыберите действие: ";
        cin >> kod;

        switch (kod) {
        case 1:
            if (start != NULL) {
                cout << "Очистите память перед созданием нового списка!" << endl;
                break;
            }
            cout << "Введите первый элемент: ";
            cin >> in;
            Create_Spis2(&start, &ennd, in);
            break;

        case 2:
            cout << "Введите элемент: ";
            cin >> in;
            cout << "Добавить в начало (0) или конец (1)? ";
            cin >> kod1;
            Add_Spis2(kod1, &start, &ennd, in);
            break;

        case 3:
            if (!start) {
                cout << "Список пуст!" << endl;
                break;
            }
            cout << "Вывести с начала (0) или с конца (1)? ";
            cin >> kod1;
            View_Spis2(kod1, (kod1 == 0 ? start : ennd));
            break;

        case 4:
            Del_All(&start, &ennd);
            break;

        case 5:
            perem(&start, &ennd, &newstart, &newend);
            cout << "Новый список: ";
            View_Spis2(0, newstart);
            break;

        case 0:
            Del_All(&start, &ennd);
            Del_All(&newstart, &newend);
            return 0;

        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    }
}
