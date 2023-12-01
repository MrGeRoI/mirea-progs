
#include <iostream>
#include <queue>
#include <stack>
#include <list>

using namespace std;

using matrix = vector<vector<int>>;
using edge = pair<int, int>;

const int INFINITY = 10000;

int find_path(matrix &f, const matrix &c, int source, int target, int vertices) // source - исток, target - сток
{
	int cur_vertex;
	// flow - значение потока через данную вершину на данном шаге поиска
	// link[i] хранит номер предыдущей вешины на пути i -> исток
	vector<int> flow(vertices);
	fill(flow.begin(), flow.end(), 0);
	vector<int> link(vertices);
	fill(flow.begin(), flow.end(), -1);
	flow[source] = INFINITY;
	vector<bool> used(vertices, false);

	stack<int> s;
	s.push(source);

	while (!s.empty())
	{
		int vertex = s.top();

		if (vertex == target)
			break;

		s.pop();

		for (int i = 0; i < vertices; i++)
			// есть ребро vertex->i, в i не заходили
			if (c[vertex][i] - f[vertex][i] > 0 && !used[i])
			{
				s.push(i);
				flow[i] = (c[vertex][i] - f[vertex][i] < flow[vertex]) ? c[vertex][i] - f[vertex][i] : flow[vertex];
				link[i] = vertex;
			}

		used[vertex] = true;
	}

	if (link[target] == -1)
		return 0;

	cur_vertex = target;

	while (cur_vertex != source)
	{
		f[link[cur_vertex]][cur_vertex] += flow[target];
		cur_vertex = link[cur_vertex];
	}

	return flow[target];
}

int max_flow(matrix &f, const matrix &c, int source, int target, int vertices) // source - исток, target - сток
{
	for (int i = 0; i < f.size(); i++)
	{
		f[i].resize(f.size());
		fill(f[i].begin(), f[i].end(), 0);
	}

	int MaxFlow = 0;
	int AddFlow;
	do
	{
		AddFlow = find_path(f, c, source, target, vertices);
		MaxFlow += AddFlow;
	} while (AddFlow > 0);
	
	return MaxFlow;
}

void print(const matrix &graph)
{
	int size = graph.size();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			cout << graph[i][j] << '\t';

		cout << '\n';
	}
}

int main()
{
	matrix graph = {{0, 0, 0, 7, 6, 0, 1, 4, 4, 5, 6, 6, 7},
					{0, 0, 6, 4, 4, 1, 2, 3, 2, 0, 1, 4, 2},
					{0, 6, 0, 8, 8, 4, 3, 6, 5, 3, 6, 6, 5},
					{7, 4, 8, 0, 5, 4, 5, 8, 0, 9, 3, 6, 8},
					{6, 4, 8, 5, 0, 1, 4, 2, 7, 7, 7, 2, 0},
					{0, 1, 4, 4, 1, 0, 7, 4, 4, 2, 4, 2, 6},
					{1, 2, 3, 5, 4, 7, 0, 7, 1, 2, 2, 9, 8},
					{4, 3, 6, 8, 2, 4, 7, 0, 8, 4, 2, 3, 2},
					{4, 2, 5, 0, 7, 4, 1, 8, 0, 2, 5, 8, 1},
					{5, 0, 3, 9, 7, 2, 2, 4, 2, 0, 5, 9, 7},
					{6, 1, 6, 3, 7, 4, 2, 2, 5, 5, 0, 9, 6},
					{6, 4, 6, 6, 2, 2, 9, 3, 8, 9, 9, 0, 5},
					{7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0}};

	print(graph);

	return 0;
}
