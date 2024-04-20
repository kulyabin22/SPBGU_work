#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class DijkstraGraph {
private:
    vector<vector<pair<int, int>>> graph;
    vector<int> dist;
    vector<bool> visited;
    vector<int> parent;
    int numvertices;


public:
    DijkstraGraph(int n) : graph(n), dist(n, numeric_limits<int>::max()), visited(n, false), numvertices(n), parent(n, -1) {} // добавляем колиичество вершин и расстоянию до каждой вершины присваиваем бесконечность

    void addEdge(int u, int v, int w) { // добавляем ребро и его вес w
        graph[u].push_back({ v, w });
    }

    void DelPath(int start, int finish) {          // функция удаления кратчайшего пути между вершинами
        for (int i = 0; i < numvertices; i++) {    // заполняем все поля начальными значениями
            dist[i] = numeric_limits<int>::max();
            visited[i] = false;
            parent[i] = -1;
        }
        dijkstra(start);
       
        for (int v = finish; v != -1; v = parent[v]) {     // перебираем ребра, начиная с конца и двигаясь по вершинам пути
            if (parent[v] != -1) {
                for (auto it = graph[parent[v]].begin(); it != graph[parent[v]].end(); ) {
                    if (it->first == v) {
                        it = graph[parent[v]].erase(it);  // удаляем ребро пути
                    }
                    else {
                        ++it;
                    }
                }
            }
        }      
        numvertices = graph.size();
    }

    void DelAllPaths(int start, int finish) {      // функция удаления всех путей между вершинами
        for (int i = 0; i < numvertices; i++){      // заполняем все поля начальными значениями
            dist[i] = numeric_limits<int>::max();
            visited[i] = false;
            parent[i] = -1;
        }
        dijkstra(start);
        while (dist[finish] != numeric_limits<int>::max()) {  // пока путь существует, удаляем его
            DelPath(start, finish);
        }
        cout << "All paths have been deleted from " << start << " to " << finish << endl;
    }

    void dijkstra(int start) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // используем приоритетную очередь для реализации бинарной кучи и расставляем элементы в ней от меньшего к большему с помощью компоратора greater
        pq.push({ 0, start });
        dist[start] = 0;

        while (!pq.empty()) {
            int u = pq.top().second; // извлекаем вершину с наименьшим расстоянием
            pq.pop();

            if (visited[u]) {
                continue;
            }
            visited[u] = true;

            for (auto& edge : graph[u]) { // перебираем все ребра исходящие из вершины u
                int v = edge.first;
                int w = edge.second;
                if (!visited[v] && dist[u] + w < dist[v]) { // если не посещали вершину и расстояние через текущую вершину меньше, чем уже известное, то обновляем расстояние и добовляем вершину в очередь
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({ dist[v], v });
                }
            }
        }
    }

    void shortestPath(int start, int finish) { // вывод кратчайшего пути
        for (int i = 0; i < numvertices; i++) {   // заполняем все поля начальными значениями
            dist[i] = numeric_limits<int>::max();
            visited[i] = false;
            parent[i] = -1;
        }
        dijkstra(start);
        if (dist[finish] == numeric_limits<int>::max()) {                          // если расстояние до вершины имеет бесконечное значение, то выводим что пути нет
            cout << "There is no way from " << start << " to " << finish << endl;
        
        }
        else{
            cout << "Shortest path langth from " << start << " to " << finish << ": " << dist[finish] << endl;
            vector <int> path;                               // находим врешиины, из которых состоит путь
            for (int v = finish; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            cout << "Shortest path: ";                       // выводим путь
            for (int i = path.size() - 1; i >= 0; --i) {
                cout << path[i] << ", ";
            }
            cout << endl;
        }       
    }
};

int main() {
    DijkstraGraph dijkstra(6);

    dijkstra.addEdge(0, 1, 7);
    dijkstra.addEdge(0, 2, 9);
    dijkstra.addEdge(0, 5, 14);
    dijkstra.addEdge(1, 2, 10);
    dijkstra.addEdge(1, 3, 15);
    dijkstra.addEdge(2, 3, 11);
    dijkstra.addEdge(2, 5, 2);
    dijkstra.addEdge(3, 4, 6);
    dijkstra.addEdge(4, 5, 9);

    dijkstra.shortestPath(0, 4);   
    dijkstra.DelPath(0, 4);
    dijkstra.shortestPath(0, 4);
    dijkstra.DelAllPaths(0, 4);
    dijkstra.shortestPath(0, 4);
    dijkstra.shortestPath(5, 3);
    
    return 0;
}
