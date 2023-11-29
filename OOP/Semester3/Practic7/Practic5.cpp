
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

using matrix = vector<vector<int>>;

// 1. Запустите функцию, реализующую алгоритм поиска в глубину,
// для перечисления всех вершин в исходном графе. Результат должен быть
// представлен с помощью одного из контейнеров STL
void bfs(const matrix &graph, vector<bool> &visited, int v)
{
	visited[v] = true;

	int size = graph.size();

	for (int i = 0; i < size; i++)
		if (v != i && graph[v][i] > 0 && !visited[i])
		{
			cout << i << ", ";
			bfs(graph, visited, i);
		}
}

void bfs(const matrix &graph)
{
	vector<bool> visited(graph.size());

	bfs(graph, visited, 0);
}

// 2. Напишите функцию для поиска минимального пути (в смысле
// суммарного веса пройденных рёбер) между i-й и всеми остальными
// пунктами, куда можно построить маршрут. Результат должен быть
// представлен с помощью одного из контейнеров STL.
vector<int> dijkstra(const matrix &graph, int v)
{
	int size = graph.size();

	vector<int> distances(size);
	queue<int> vertex;

	for (int i = 0; i < 10; i++)
		distances[i] = 10000;

	vertex.push(0);
	distances[0] = 0;

	while (!vertex.empty())
	{
		int cur_vertex = vertex.front();
		vertex.pop();

		for (int i = 0; i < size; i++)
			if (graph[cur_vertex][i] != 0 && distances[i] > distances[cur_vertex] + graph[cur_vertex][i])
			{
				vertex.push(i);
				distances[i] = distances[cur_vertex] + graph[cur_vertex][i];
			}
	}

	return distances;
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

	bfs(graph);

	cout << endl;

	vector<int> distances = dijkstra(graph, 5);

	for (int i = 0; i < graph.size(); i++)
		cout << "5 -> " << i << ": " << distances[i] << endl;

	return 0;
}
