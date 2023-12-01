
#include <iostream>
#include <queue>
#include <stack>
#include <list>

using namespace std;

struct edge
{
public:
	int from, to;

	edge()
	{
		from = to = 0;
	}

	edge(int f, int t)
	{
		from = f;
		to = t;
	}
};

// 1. Запустите функцию, реализующую алгоритм поиска в глубину,
// для перечисления всех вершин в исходном графе. Результат должен быть
// представлен с помощью одного из контейнеров STL
void dfs(const vector<vector<int>> &graph, int start, vector<int> &out_vertex)
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
vector<int> dijkstra(const vector<vector<int>> &graph, int v)
{
	int size = graph.size();

	vector<int> distances(size);
	queue<int> vertex;

	for (int i = 0; i < distances.size(); i++)
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

// 3. Реализовать функцию подсчета степени (количества
// инцидентных ребер) вершин в полученном дереве (обход дерева сделать на
// основе поиска в ширину). Реализовать функцию подсчета средней степени по
// всему дереву.
void spanning_tree(vector<vector<int>> &graph, list<edge> &tree_edges, vector<int> &degrees)
{
	int mst_weight = 0;						// Текущий вес остова.
	list<edge> edges;						// рассматриваемые ребра
	vector<bool> used(graph.size(), false); // использованные вершины
	degrees.resize(graph.size());

	used[0] = true; // Начнём с вершины 0.
	for (int i = 0; i < graph.size(); i++)
		if (graph[0][i] > 0)
			edges.push_back(edge(0, i));

	while (!edges.empty())
	{
		list<edge>::iterator min_it = edges.begin(), it = edges.begin();

		int min_weight = graph[it->from][it->to];

		for (; it != edges.end(); it++)
		{
			int weight = graph[it->from][it->to];

			if (weight != 0 && weight < min_weight)
			{
				min_it = it;
				min_weight = weight;
			}
		}

		edge min_edge = *min_it;
		edges.erase(min_it);

		if (used[min_edge.to])
			continue;

		used[min_edge.to] = true;
		tree_edges.push_back(min_edge);
		degrees[min_edge.from]++;
		degrees[min_edge.to]++;
		mst_weight += graph[min_edge.from][min_edge.to];

		for (int i = 0; i < graph.size(); i++)
			if (graph[min_edge.to][i] > 0 && !used[i])
				edges.push_back(edge(min_edge.to, i));
	}
}
void bfs(const vector<vector<int>> &graph, vector<bool> &visited, int v)
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

void bfs(const vector<vector<int>> &graph)
{
	vector<bool> visited(graph.size());

	bfs(graph, visited, 0);
}

// 4. Реализуйте функцию построения минимального остова на основе
// алгоритма Прима и примените её на исходном графе.
void prime_algo(const vector<vector<int>> &graph, vector<vector<int>> &tree)
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

		int min_weight = graph[it->from][it->to];

		for (; it != edges.end(); it++)
		{
			int weight = graph[it->from][it->to];

			if (weight != 0 && weight < min_weight)
			{
				min_it = it;
				min_weight = weight;
			}
		}

		edge min_edge = *min_it;
		edges.erase(min_it);

		if (used[min_edge.to])
			continue;

		used[min_edge.to] = true;
		tree[min_edge.from][min_edge.to] = graph[min_edge.from][min_edge.to];
		tree[min_edge.to][min_edge.from] = graph[min_edge.to][min_edge.from];
		mst_weight += graph[min_edge.from][min_edge.to];

		for (int i = 0; i < graph.size(); i++)
			if (graph[min_edge.to][i] > 0 && !used[i])
				edges.push_back(edge(min_edge.to, i));
	}
}

void print(const vector<vector<int>> &graph)
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
	vector<vector<int>> graph = {{0, 1, 4, 4, 8, 5, 6, 7, 5, 2, 4, 2},
								 {1, 0, 6, 9, 1, 2, 3, 1, 2, 8, 9, 5},
								 {4, 6, 0, 7, 4, 8, 9, 6, 2, 6, 7, 6},
								 {4, 9, 7, 0, 2, 0, 0, 8, 8, 8, 7, 8},
								 {8, 1, 4, 2, 0, 3, 9, 2, 7, 7, 3, 1},
								 {5, 2, 8, 0, 3, 0, 0, 6, 4, 4, 5, 3},
								 {6, 3, 9, 0, 9, 0, 0, 2, 2, 9, 2, 3},
								 {7, 1, 6, 8, 2, 6, 2, 0, 7, 4, 2, 6},
								 {5, 2, 2, 8, 7, 4, 2, 7, 0, 3, 4, 6},
								 {2, 8, 6, 8, 7, 4, 9, 4, 3, 0, 3, 4},
								 {4, 9, 7, 7, 3, 5, 2, 2, 4, 3, 0, 7},
								 {2, 5, 6, 8, 1, 3, 3, 6, 6, 4, 7, 0}};

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
		cout << "(" << e.from << "," << e.to << ") " << endl;

	for (int i = 0; i < tree_degrees.size(); i++)
		cout << i << ": " << tree_degrees[i] << endl;

	vector<vector<int>> span;

	prime_algo(graph, span);

	print(span);

	cout << "dfs spanning: ";

	vertex.clear();

	dfs(span, 0, vertex);

	for (int i = 0; i < vertex.size(); i++)
		cout << i << ", ";
	cout << endl;

	distances = dijkstra(span, 5);

	for (int i = 0; i < span.size(); i++)
		cout << "5 -> " << i << ": " << distances[i] << endl;

	return 0;
}
