#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

class Dinic {
private:
    struct Edge {  // ��������� ������������� �����
        int to, capacity, flow;
        Edge(int to, int capacity) : to(to), capacity(capacity), flow(0) {}
    };

    int n, s, t; // ����� ������, ������, �����
    vector<vector<int>> cap; // ������ ���������
    vector<Edge> edges; // ������ �����
    vector<int> level; // ������ ������
    vector<int> ptr; // ��������� �� ������� �����

    bool bfs() {
        level.assign(n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i : cap[u]) {
                Edge& e = edges[i];
                if (level[e.to] == -1 && e.flow < e.capacity) { // ���� ����� ����� �� ������� � �� ����� ����� ���������� �����, �� ��������� ������� � �������
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int flow) {
        if (u == t) return flow;
        for (; ptr[u] < cap[u].size(); ptr[u]++) {
            int id = cap[u][ptr[u]];
            Edge& e = edges[id];
            if (level[e.to] == level[u] + 1 && e.flow < e.capacity) {  // ���� ����� ����� �� ������� ������, ��� ������� ������� u � �� ����� ����� ���������� �����
                int pushed = dfs(e.to, min(flow, e.capacity - e.flow)); // �� ���� ������������ ����� �� �������������� ���� �� ����� �����
                if (pushed > 0) {
                    e.flow += pushed;
                    edges[id ^ 1].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

public:
    Dinic(int n, int s, int t) : n(n), s(s), t(t), cap(n), level(n), ptr(n) {}

    void addEdge(int from, int to, int capacity) { // ���������� �����
        edges.emplace_back(to, capacity);
        cap[from].push_back(edges.size() - 1);
        edges.emplace_back(from, 0);
        cap[to].push_back(edges.size() - 1);
    }

    int maxFlow() { // ����� ������������� ������
        int flow = 0;
        while (bfs()) {  // ���� ���� ������������� ����
            ptr.assign(n, 0);
            int pushed;
            while ((pushed = dfs(s, INT_MAX)) > 0) {  // ���� ���� ������������� ���� �� ���������
                flow += pushed; // ����������� ������� �����
            }
        }
        return flow;
    }
};

int main() {
    int s, t;
    int n = 6;
    cin >> s >> t; // ���� ������ � �����
    vector<vector<int>> graph = { { 0, 18, 12, 0, 0, 0 }, { 0, 0, 0, 0, 16, 0 },
            { 0, 0, 0, 6, 5, 0 },  { 0, 0, 0, 0, 11, 3 },
            { 0, 0, 0, 0, 0, 10 },   { 0, 0, 0, 0, 0, 0 } };

    Dinic dinic(n, s, t);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dinic.addEdge(i, j, graph[i][j]);
        }
    }

    cout << "The maximum flow is " << dinic.maxFlow() << endl;
    return 0;
}
