
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph {
    int n, m;  // Количество вершин и дуг
    vector<vector<int>> matrix;  // Матрица инцидентности
};

void InputMatrix(Graph* graph) {
    cout << "Введите количество вершин и дуг: ";
    cin >> graph->n >> graph->m;

    graph->matrix.resize(graph->n, vector<int>(graph->m, 0));

    cout << "Введите элементы матрицы инцидентности (" << graph->n << " строк и " << graph->m << " столбцов):\n";
    for (int i = 0; i < graph->n; i++) {
        for (int j = 0; j < graph->m; j++) {
            cin >> graph->matrix[i][j];
        }
    }
}

void PrintMatrix(const Graph* graph) {
    cout << "\nМатрица инцидентности:\n";
    for (const auto& row : graph->matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void AddVertex(Graph* graph) {
    vector<int> newVertex(graph->m, 0);
    graph->matrix.push_back(newVertex);
    graph->n++;
    cout << "Вершина добавлена.\n";
}

void DelVertex(Graph* graph) {
    int numVertex;
    cout << "\nВведите номер вершины для удаления: ";
    cin >> numVertex;

    numVertex--;
    if (numVertex >= 0 && numVertex < graph->n) {
        for (int i = graph->matrix[0].size() - 1; i >= 0; i--) {
            if (graph->matrix[numVertex][i] != 0) {
                for (int k = 0; k < graph->n; k++) {
                    graph->matrix[k].erase(graph->matrix[k].begin() + i);
                }
                graph->m--;
            }
        }
        graph->matrix.erase(graph->matrix.begin() + numVertex);
        cout << "Вершина " << numVertex + 1 << " удалена.\n";
        graph->n--;
    }
    else {
        cout << "Ошибка: некорректный индекс.\n";
    }
}

void AddArc(Graph* graph) {
    int fromVertex, toVertex;
    cout << "\nВведите 2 вершины (откуда -> куда): ";
    cin >> fromVertex >> toVertex;
    fromVertex--;
    toVertex--;

    if (fromVertex < 0  fromVertex >= graph->n  toVertex < 0  toVertex >= graph->n  fromVertex == toVertex) {
        cout << "Ошибка: некорректные индексы.\n";
        return;
    }

    for (int i = 0; i < graph->n; i++) {
        if (i == fromVertex) {
            graph->matrix[i].push_back(-1);
        }
        else if (i == toVertex) {
            graph->matrix[i].push_back(1);
        }
        else {
            graph->matrix[i].push_back(0);
        }
    }
    graph->m++;
    cout << "Дуга добавлена.\n";
}

void DelArc(Graph* graph) {
    int numArc;
    cout << "\nВведите номер дуги для удаления: ";
    cin >> numArc;

    if (numArc > 0 && numArc <= graph->m) {
        for (int i = 0; i < graph->n; i++) {
            graph->matrix[i].erase(graph->matrix[i].begin() + numArc - 1);
        }
        graph->m--;
        cout << "Дуга удалена.\n";
    }
    else {
        cout << "Ошибка: некорректный индекс.\n";
    }
}

void BFS(Graph* graph) {
    int firstVertex;
    cout << "Введите начальную вершину для обхода: ";
    cin >> firstVertex;
    firstVertex--;

    if (firstVertex < 0 || firstVertex >= graph->n) {
        cout << "Ошибка: некорректный индекс.\n";
        return;
    }

    queue<int> q;
    vector<bool> visited(graph->n, false);

    q.push(firstVertex);
    visited[firstVertex] = true;

    cout << "Обход в ширину:\n";

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << "Посещена вершина: " << v + 1 << endl;

        for (int u = 0; u < graph->m; u++) {
            if (graph->matrix[v][u] == -1) {
                for (int k = 0; k < graph->n; k++) {
                    if (graph->matrix[k][u] == 1 && !visited[k]) {
                        visited[k] = true;
                        q.push(k);
                        cout << "Переход из " << v + 1 << " в " << k + 1 << endl;
                    }
                }
            }
        }
    }
    cout << "Обход завершён.\n";
}


void ShowMenu() {
    cout << "=== Меню ===\n";
    cout << "1. Вывести матрицу\n";
    cout << "2. Добавить вершину\n";
    cout << "3. Удалить вершину\n";
    cout << "4. Добавить дугу\n";
    cout << "5. Удалить дугу\n";
    cout << "6. Обход в ширину\n";
    cout << "7. Выход\n";
    cout << "Выберите опцию: ";
}

void prog() {
    setlocale(LC_ALL, "ru");
    Graph* graph = new Graph();
    InputMatrix(graph);

    int choice;
    do {
        ShowMenu();
        cin >> choice;
        switch (choice) {
        case 1: PrintMatrix(graph); break;
        case 2: AddVertex(graph); break;
        case 3: DelVertex(graph); break;
        case 4: AddArc(graph); break;
        case 5: DelArc(graph); break;
        case 6: BFS(graph); break;
        case 7: cout << "До свидания!\n"; break;
        default: cout << "Ошибка: неверный выбор.\n"; break;
        }
    } while (choice != 7);

    delete graph;
}
