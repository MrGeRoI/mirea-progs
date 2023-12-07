
#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <functional>

using namespace std;

using matrix = vector<vector<int>>;
using edge = pair<int, int>;

// 1. Запустите функцию, реализующую алгоритм поиска в глубину,
// для перечисления всех вершин в исходном графе. Результат должен быть
// представлен с помощью одного из контейнеров STL
void dfs(const matrix &graph, int start, vector<int> &out_vertex)
{
	vector<bool> visited(graph.size(), false);
	stack<int> vertex;
	vertex.push(start);
	visited[start] = true;

	cout << start << ", ";

	while (!vertex.empty())
	{
		int v = vertex.top();
		vertex.pop();

		for (int i = 0; i < graph.size(); i++)
		{
			if (graph[v][i] != 0 && !visited[i])
			{
				visited[i] = true;
				out_vertex.push_back(i);
				vertex.push(i);
			}
		}
	}
}

// 2. Напишите функцию для поиска минимального пути (в смысле
// суммарного веса пройденных рёбер) между i-й и всеми остальными
// пунктами, куда можно построить маршрут. Результат должен быть
// представлен с помощью одного из контейнеров STL.
vector<int> dijkstra(const matrix &graph, int v = 0)
{
	int size = graph.size();

	vector<int> distances(size);

	priority_queue<int, vector<int>, function<bool(int, int)>> vertex([distances](int x, int y)
																	  { return distances[x] > distances[y]; });

	for (int i = 0; i < distances.size(); i++)
		distances[i] = 10000;

	distances[v] = 0;
	vertex.push(v);

	while (!vertex.empty())
	{
		int cur_vertex = vertex.top();
		vertex.pop();

		for (int i = 0; i < size; i++)
			if (graph[cur_vertex][i] != 0 && distances[i] > distances[cur_vertex] + graph[cur_vertex][i])
			{
				distances[i] = distances[cur_vertex] + graph[cur_vertex][i];
				vertex.push(i);
			}
	}

	return distances;
}

// 3. Реализовать функцию подсчета степени (количества
// инцидентных ребер) вершин в полученном дереве (обход дерева сделать на
// основе поиска в ширину). Реализовать функцию подсчета средней степени по
// всему дереву.
void spanning_tree(const matrix &graph, list<edge> &tree_edges, vector<int> &degrees)
{
	int mst_weight = 0;						// Текущий вес остова.					
	vector<bool> used(graph.size(), false); // использованные вершины
	priority_queue<edge, vector<edge>, function<bool(edge, edge)>> edges([graph](const edge& x, const edge& y) 
																	  { return graph[x.first][x.second] > graph[y.first][y.second]; }); // рассматриваемые ребра

	degrees.resize(graph.size());

	used[0] = true; // Начнём с вершины 0.
	for (int i = 0; i < graph.size(); i++)
		if (graph[0][i] > 0)
			edges.push(edge(0, i));

	while (!edges.empty())
	{
		edge min_edge = edges.top();
		edges.pop();

		if (used[min_edge.second])
			continue;

		used[min_edge.second] = true;
		tree_edges.push_back(min_edge);
		degrees[min_edge.first]++;
		degrees[min_edge.second]++;
		mst_weight += graph[min_edge.first][min_edge.second];

		for (int i = 0; i < graph.size(); i++)
			if (graph[min_edge.second][i] > 0 && !used[i])
				edges.push(edge(min_edge.second, i));
	}
}
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

// 4. Реализуйте функцию построения минимального остова на основе
// алгоритма Прима и примените её на исходном графе.
void prime_algo(const matrix &graph, matrix &tree)
{
	int mst_weight = 0;						// Текущий вес остова.
	list<edge> edges;						// рассматриваемые ребра
	vector<bool> used(graph.size(), false); // использованные вершины

	tree.resize(graph.size());

	used[0] = true; // Начнём с вершины 0.
	for (int i = 0; i < graph.size(); i++)
	{
		if (graph[0][i] > 0)
			edges.push_back(edge(0, i));

		tree[i].resize(graph.size());
	}

	while (!edges.empty())
	{
		list<edge>::iterator min_it = edges.begin(), it = edges.begin();

		int min_weight = graph[it->first][it->second];

		for (; it != edges.end(); it++)
		{
			int weight = graph[it->first][it->second];

			if (weight != 0 && weight < min_weight)
			{
				min_it = it;
				min_weight = weight;
			}
		}

		edge min_edge = *min_it;
		edges.erase(min_it);

		if (used[min_edge.second])
			continue;

		used[min_edge.second] = true;
		tree[min_edge.first][min_edge.second] = graph[min_edge.first][min_edge.second];
		tree[min_edge.second][min_edge.first] = graph[min_edge.second][min_edge.first];
		mst_weight += graph[min_edge.first][min_edge.second];

		for (int i = 0; i < graph.size(); i++)
			if (graph[min_edge.second][i] > 0 && !used[i])
				edges.push_back(edge(min_edge.second, i));
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
					{7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0}};

	print(graph);

	cout << "dfs: ";

	vector<int> vertex;

	dfs(graph, 0, vertex);

	for (int i = 0; i < vertex.size(); i++)
		cout << i << ", ";
	cout << endl;

	vector<int> distances = dijkstra(graph, 5);

	for (int i = 0; i < graph.size(); i++)
		cout << "5 -> " << i << ": " << distances[i] << endl;

	list<edge> tree_edges;
	vector<int> tree_degrees;

	spanning_tree(graph, tree_edges, tree_degrees);

	for (edge e : tree_edges)
		cout << "(" << e.first << "," << e.second << ") " << endl;

	for (int i = 0; i < tree_degrees.size(); i++)
		cout << i << ": " << tree_degrees[i] << endl;

	matrix span;

	prime_algo(graph, span);

	print(span);

	cout << "dfs spanning: ";

	vertex.clear();

	dfs(span, 0, vertex);

	for (int i = 0; i < vertex.size(); i++)
		cout << i << ", ";
	cout << endl;

	distances = dijkstra(span, 5);

	for (int i = 0; i < distances.size(); i++)
		if (i != 5)
			cout << "5 -> " << i << ": " << distances[i] << endl;

	return 0;
}
