#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, k; // ���������� ������ � �����
vector < vector<int> > g;
vector<int> mt;
vector<bool> used;
vector <int> side; // ��� ����� ���� �������� 0, ��� ������ 1

void bfs(int start) { // ���������� ����� �� ����
	queue<int> q;
	q.push(start);
	side[start] = 0;

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int u : g[v]){
			if (side[u] == -1) {
				side[u] = 1 - side[v];
				q.push(u);
			}
		}
	}
}

bool try_kuhn(int v) {
	if (used[v]) return false;
	used[v] = true;
	for (int u : g[v]) {
		if (mt[u] == -1 || try_kuhn(mt[u])) {
			mt[u] = v;
			return true;
		}
	}
	return false;
}

int main() {
	cin >> n >> k; // ���� ���������� ������ � �����

	g.resize(n);
	mt.assign(k, -1);
	side.assign(n, -1);

	for (int i = 0; i < k; i++) { // ���������� �����
		int a, b;
		cin >> a >> b;
		a--;  
		b--;  
		g[a].push_back(b);
		g[b].push_back(a);
	}

	bfs(0);

	// ����������, � ����� ���� ������ ������
	int leftcount = 0, rightcount = 0;
	for (int i = 0; i < n; i++) {
		if (side[i] == 0) leftcount++;
		else rightcount++;
	}

	int match = 0; // ������� �������������
	// ��������� �������� ���� � ����, � ������� ������ ������
	if (leftcount < rightcount) {
		for (int v = 0; v < n; v++) {
			if (side[v] == 0) {
				used.assign(n, false);
				if (try_kuhn(v)) {
					match++;
				}
			}
		}
	}
	else {
		for (int v = 0; v < n; v++) {
			if (side[v] == 1) {
				used.assign(n, false);
				if (try_kuhn(v)) {
					match++;
				}
			}
		}
	}

	cout << match << endl;
	for (int i = 0; i < k; i++) {
		if (mt[i] != -1) {
			cout << mt[i] + 1 << " " << i + 1 << endl;
		}
	}

	return 0;
}