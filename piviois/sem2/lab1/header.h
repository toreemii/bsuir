#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Graph {
    int n;
    int m;
    vector<vector<int>> matrix;
};
    void InputMatrix(Graph* graph);
    void PrintMatrix(Graph* graph);
    void AddVertex(Graph* graph);
    void DelVertex(Graph* graph);
    void AddArc(Graph* graph);
    void DelArc(Graph* graph);
    void BFS(Graph* graph);

    void ShowMenu();
    void prog();
