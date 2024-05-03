#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>

using namespace std;

#define numv 6

bool bfs(int rgraph[numv][numv], int s, int f, int parent[]) {
	bool visited[numv];
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < numv; v++) {
			if (visited[v] == false && rgraph[u][v] > 0) {
				if (v == f) {
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}

	}
	return false;
}

int fordFulkerson(int graph[numv][numv], int s, int f) {
	int u, v;
	int rgraph[numv][numv];
	for (u = 0; u < numv; u++) {
		for (v = 0; v < numv; v++) {
			rgraph[u][v] = graph[u][v];
		}
	}
	int parent[numv];
	int maxflow = 0;

	while (bfs(rgraph, s, f, parent)) {
		int pathflow = INT_MAX;
		for (v = f; v != s; v = parent[v]) {
			u = parent[v];
			pathflow = min(pathflow, rgraph[u][v]);
		}
		for (v = f; v != s; v = parent[v]) {
			u = parent[v];
			rgraph[u][v] -= pathflow;
			rgraph[v][u] += pathflow;
		}
		maxflow += pathflow;
	}
	return maxflow;
}

int main() {
	int graph[numv][numv] = { { 0, 18, 12, 0, 0, 0 }, { 0, 0, 0, 0, 16, 0 },
			{ 0, 0, 0, 6, 5, 0 },  { 0, 0, 0, 0, 11, 3 },
			{ 0, 0, 0, 0, 0, 10 },   { 0, 0, 0, 0, 0, 0 } };

	cout << "The maximum flow is " << fordFulkerson(graph, 0, 5);

	return 0;
}