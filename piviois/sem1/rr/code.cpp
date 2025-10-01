#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

// Определение структуры графа
struct Graph {
    unordered_map<int, vector<int>> adjList;
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
};

// Функция для поиска звёзд с заданным числом листьев
vector<pair<int, vector<int>>> findStars(Graph& graph, int k) {
    vector<pair<int, vector<int>>> stars;

    for (auto& vertex : graph.adjList) {
        if (vertex.second.size() >= k) {
            vector<int> leaves;
            for (int neighbor : vertex.second) {
                if (graph.adjList[neighbor].size() == 1) {
                    leaves.push_back(neighbor);
                }
            }
            if (leaves.size() >= k) {
                stars.push_back({ vertex.first, vector<int>(leaves.begin(), leaves.begin() + k) });
            }
        }
    }

    return stars;
}

int main() {
    setlocale(LC_ALL,"ru");
    Graph graph;
    int numEdges;
    cout << "Введите количество рёбер в графе: ";
    cin >> numEdges;
    cin.ignore();

    if (numEdges == 0) {
        cout << "Пустой граф" << endl;
        return 0;
    }
    else {
        cout << "Введите рёбра в формате 'u v' (без кавычек), где u и v - вершины графа:\n";
        for (int i = 0; i < numEdges; ++i) {
            string edge;
            getline(cin, edge);
            stringstream ss(edge);
            int u, v;
            ss >> u >> v;
            graph.addEdge(u, v);
        }
    }

    int k;
    cout << "Введите заданное число листьев: ";
    cin >> k;

    vector<pair<int, vector<int>>> stars = findStars(graph, k);

    if (stars.empty()) {
        cout << "Звезды с " << k << " листьями не найдены.\n";
    }
    else {
        cout << "Найденные звезды:\n";
        for (auto& star : stars) {
            cout << "Центр звезды: " << star.first << ", Листья: ";
            for (int leaf : star.second) {
                cout << leaf << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
