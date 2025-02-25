#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int n;
    int m;
    vector<vector<int>> matrix;
public:

    void InputMatrix() {
        cout << "Введите количество вершин и дуг: ";
        cin >> n >> m;

        matrix.resize(n, vector<int>(m, 0));

        cout << "Введите элементы матрицы инцидентности (" << n << " строк и " << m << " столбцов):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> matrix[i][j];
            }
        }
    }

    void PrintMatrix() {
        cout << "\nМатрица инцидентности:" << endl;
        for (const auto& n : matrix) {
            for (int val : n) {
                cout << val << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void AddVertex() {
        vector<int> newVertex(m, 0);
        matrix.push_back(newVertex);
        n++;
        cout << "Вершина добавлена." << endl << endl;
    }
    void DelVertex()
    {
        int numVertex;
        cout << endl << "Выберите вершину, которую хотите удалить: " << endl;
        cin >> numVertex;

        numVertex--;
        if (numVertex >= 0 && numVertex < n){
            for (int i = matrix[0].size() - 1; i >= 0; i--){
                if (matrix[numVertex][i] != 0){
                    for (int k = 0; k < n; k++){
                        matrix[k].erase(matrix[k].begin() + i);
                    }
                    m--;
                }
            }
            matrix.erase(matrix.begin() + numVertex);
            cout << "Вершина " << ++numVertex << " удалена." << endl;
            n--;
        }
        else{
            cout << "Недопустимый индекс для удаления элемента." << endl;
            return;
        }
    }
    void AddArc()
    {
        int fromVertex, toVertex;
        cout << endl << "Введите 2 вершины, от которой и до которой будет проведена дуга: " << endl;
        cin >> fromVertex >> toVertex;
        fromVertex--;
        toVertex--;
        if (fromVertex == toVertex){
            cout << "Невозможно создать петлю. Введите 2 корректных индекса." << endl;
            return;
        }
        if ((fromVertex >= 0 && fromVertex < matrix.size()) && (toVertex >= 0 && toVertex < matrix.size())){
            for (int i = 0; i < n; i++){
                if (i == fromVertex){
                    matrix[i].push_back(-1);
                }
                else if (i == toVertex){
                    matrix[i].push_back(1);
                }
                else{
                    matrix[i].push_back(0);
                }
            }
            m++;
        }
        else{
            cout << "Недопустимый индекс." << endl;
            return;
        }
        cout << "Дуга от вершины " << fromVertex + 1 << " до вершины " << toVertex + 1 << " добавлена." << endl;
    }
    void DelArc()
    {
        int numArc;
        cout << endl << "Введите номер дуги, которую хотите удалить: " << endl;
        cin >> numArc;

        if (numArc >= 0 && numArc <= matrix[0].size()){
            for (int i = 0; i < n; i++){
                matrix[i].erase(matrix[i].begin() + numArc - 1);
            }
            m--;
            cout << "Дуга удалена." << endl;
        }
        else {
            cout << "Недопустимый индекс." << endl;
            return;
        }
    }

    void BFS() {
        int firstVertex;
        cout << "Введите номер вершины, с которой начать обход в ширину: ";
        cin >> firstVertex;

        if (cin.fail() || firstVertex < 1 || firstVertex > n) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Некорректный ввод." << endl;
            return;
        }

        firstVertex--; 
        queue<int> q;
        vector<bool> visited(n, false); 

        q.push(firstVertex);
        visited[firstVertex] = true; 

        cout << "Дерево обхода в ширину:" << endl;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << "Посещена вершина: " << v + 1 << endl;


            for (int u = 0; u < m; u++) { // u индекс дуги
                if (matrix[v][u] == -1) { 
                    for (int k = 0; k < n; k++) { 
                        if (matrix[k][u] == 1 && !visited[k]) { 
                            visited[k] = true; 
                            q.push(k); 
                            cout << "Из вершины " << v + 1 << " в вершину " << k + 1 << endl; 
                        }
                    }
                }
            }
        }
        cout << "Обход в ширину окончен." << endl;
    }
};
void ShowMenu() {
    cout << "=== Меню ===\n";
    cout << "1. Вывести матрицу\n";
    cout << "2. Добавить вершину\n";
    cout << "3. Удалить вершину\n";
    cout << "4. Добавить дугу\n";
    cout << "5. Удалить дугу\n";
    cout << "6. Обойти граф в ширину\n";
    cout << "7. Выход\n";
    cout << "Выберите опцию: ";
}

int main() {
    setlocale(LC_ALL, "ru");
    Graph graph;
    graph.InputMatrix();
    int choice;
    do {
        ShowMenu();
        cin >> choice;
        switch (choice) {
        case 1: graph.PrintMatrix(); break;
        case 2: graph.AddVertex(); break;
        case 3: graph.DelVertex(); break;
        case 4: graph.AddArc(); break;
        case 5: graph.DelArc(); break;
        case 7: cout << "До свидания!" << endl; break;
        default: cout << "Неверный выбор." << endl; break;
        }
    } while (choice != 7);
    return 0;
}
