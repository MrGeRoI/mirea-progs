
#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <functional>

using namespace std;

using matrix = vector<vector<int>>;

const int INFINITY = 10000;

int find_path(const matrix &graph, matrix &total_flow, int source, int target) // source - исток, target - сток
{
	int cur_vertex, vertices = graph.size();
	// flow - значение потока через данную вершину на данном шаге поиска
	// link[i] хранит номер предыдущей вешины на пути i -> исток
	vector<int> flow(vertices);
	fill(flow.begin(), flow.end(), 0);
	vector<int> link(vertices);
	fill(flow.begin(), flow.end(), -1);
	flow[source] = INFINITY;
	vector<bool> used(vertices, false);

	priority_queue<int, vector<int>, function<bool(int, int)>> vertex([flow](int x, int y)
																	  { return flow[x] < flow[y]; });

	vertex.push(source);

	while (!vertex.empty())
	{
		int v = vertex.top();

		if (v == target)
			break;

		vertex.pop();

		for (int i = 0; i < vertices; i++)
			// есть ребро v->i, в i не заходили
			if (graph[v][i] - total_flow[v][i] > 0 && !used[i])
			{
				flow[i] = (graph[v][i] - total_flow[v][i] < flow[v]) ? graph[v][i] - total_flow[v][i] : flow[v];
				link[i] = v;

				vertex.push(i);
			}

		used[v] = true;
	}

	if (link[target] == -1)
		return 0;

	cur_vertex = target;

	while (cur_vertex != source)
	{
		total_flow[link[cur_vertex]][cur_vertex] += flow[target];
		cur_vertex = link[cur_vertex];
	}

	return flow[target];
}

// Используя граф из задачи №5.1, найдите максимальный поток
// между вершиной 0 и вершиной с максимальным индексом. Вес рёбер считать
// пропускной способностью.
int max_flow(const matrix &graph, matrix &flow, int source, int target) // source - исток, target - сток
{
	int vertices = graph.size();

	flow.resize(vertices);

	for (int i = 0; i < flow.size(); i++)
	{
		flow[i].resize(graph[i].size());
		fill(flow[i].begin(), flow[i].end(), 0);
	}

	int MaxFlow = 0;
	int AddFlow;
	do
	{
		AddFlow = find_path(graph, flow, source, target);
		MaxFlow += AddFlow;
	} while (AddFlow > 0);

	return MaxFlow;
}

// Напишите функцию, решающую задачу о поиске гамильтонова
// цикла: необходимо вернуть путь (последовательность вершин),
// составляющих цикл, если он есть (используйте граф из задачи №5.1).
bool hamilton(const matrix &mat, vector<bool> &visited, vector<int> &path, int curr)
{
	int vertices = mat.size();
	// путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
	// если нет, откатываемся на шаг назад
	path.push_back(curr);

	// вершина использована в пути
	visited.resize(vertices);
	visited[curr] = true;

	// проверить всех непосещенных соседей вершины curr
	// if (path.size() == vertices) return true; //mat.size()
	if (path.size() == vertices && mat[path[path.size() - 1]][path[0]] != 0)
		return true;

	if (path.size() == vertices && mat[path[path.size() - 1]][path[0]] == 0)
	{
		visited[curr] = false;
		path.pop_back();
		return false;
	}

	for (int i = 0; i < vertices; i++)
	{
		if (mat[curr][i] > 0 && !visited[i])
			if (hamilton(mat, visited, path, i))
				return true;
	}

	// этот путь не подходит, убираем вершину и откатываемся
	visited[curr] = false;
	path.pop_back();
	return false;
}

// Напишите функцию, решающую задачу о закраске графа с
// помощью жадного алгоритма (используйте граф из задачи №5.1).
void paint_graph(const matrix &graph, vector<int> &color, int curr)
{
	int vertices = graph.size();
	color.resize(vertices);

	// структура данных для цветов смежных вершин с исследуемой
	set<int> neighbours;

	// аналоги поиска в ширину
	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		// вершина уже закрашена?
		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < vertices; next++)
			if (graph[curr][next] == 1)
			{
				// проверяем цвета всех смежных вершин
				neighbours.insert(color[next]);

				if (color[next] == 0)
					q.push(next);
			}

		// счетчик цветов - ищем допустимый цвет с наименьшим индексом
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
			// есть ли этот номер цвета среди соседей?
			if (neighbours.find(color_counter) == neighbours.end())
				break;

			color_counter++;
		} while (true);

		// красим вершину в допустимый цвет
		color[curr] = color_counter;
	}
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
					{7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0}},
		   flow;

	print(graph);

	// Максимальный поток: 45
	cout << "Max flow: " << max_flow(graph, flow, 0, graph.size() - 1) << endl;

	vector<bool> visited;
	vector<int> path, color;

	// Цикл: 4 -> 0 -> 3 -> 1 -> 2 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> 12 -> 11 -> 4
	if (hamilton(graph, visited, path, 4))
		for (int i : path)
			cout << i << " -> ";

	cout << endl;

	paint_graph(graph, color, 0);

	// Покраска: (0: 1); (1: 0); (2: 0); (3: 0); (4: 0); (5: 0); (6: 2); (7: 0); (8: 1); (9: 0); (10: 0); (11: 0); (12: 2);
	for (int i = 0; i < color.size(); i++)
		cout << '(' << i << ": " << color[i] << "); ";

	cout << endl;

	return 0;
}
