#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stdexcept>
#include <functional>

using namespace std;

// Исключение на графе
class GraphException : exception
{
public:
	virtual const char *what() const noexcept { return "GraphException"; };
};

// Исключение на графе: неправильный индекс вершины
class WrongVertexException : GraphException
{
public:
	virtual const char *what() const noexcept { return "WrongVertexException"; };
};

// Класс неореинтированного незвешенного графа
class Graph
{
public:
	// Класс ребра
	struct Edge
	{
	public:
		// От куда и куда
		int _from, _to;

		// Конструктор по умолчанию
		Edge() { _from = _to = -1; }

		Edge(int from, int to)
		{
			_from = from;
			_to = to;
		}

		// Конструктор копий
		Edge(const Edge &edge) : _from(edge._from), _to(edge._to) {}

		Edge &operator=(const Edge &edge)
		{
			_from = edge._from;
			_to = edge._to;

			return *this;
		}
	};

private:
	// Матрица смежности вершин графа
	vector<vector<int>> _matrix;

public:
	// Конструктор графа
	// vertices: кол-во вершин
	Graph(int vertices) : _matrix(vertices)
	{
		for (int i = 0; i < vertices; i++)
			_matrix[i].resize(vertices);
	}

	// Конструктор графа
	// matrix: матрица смежности
	Graph(const vector<vector<int>> &matrix) : _matrix(matrix) {}

	// Конструктор копий
	Graph(const Graph &graph) : _matrix(graph._matrix) {}

	// Создать ребро (x,y)
	// x, y: вершины
	void connect(int x, int y)
	{
		if (x < 0 || x >= _matrix.size() || y < 0 || y >= _matrix.size())
			throw WrongVertexException();

		_matrix[x][y] = _matrix[y][x] = true;
	}

	// Удалить ребро (x,y)
	// x, y: вершины
	void disconnect(int x, int y)
	{
		if (x < 0 || x >= _matrix.size() || y < 0 || y >= _matrix.size())
			throw WrongVertexException();

		_matrix[x][y] = _matrix[y][x] = false;
	}

	// Свявзаны ли вершины ребром
	// x, y: вершины
	bool isConnected(int x, int y) const
	{
		if (x < 0 || x >= _matrix.size() || y < 0 || y >= _matrix.size())
			throw WrongVertexException();

		return _matrix[x][y];
	}

	// Найти путь из вершины в другую вершину
	// source, target: вершины
	// Возвращает: путь из вершин
	list<int> findPath(int source, int target) const
	{
		int n = _matrix.size();																// Количество вершин в графе
		vector<int> dist(n, INT_MAX);														// Массив для хранения расстояний от начальной вершины до остальных
		vector<int> parent(n, -1);															// Массив для хранения предыдущей вершины на пути к каждой вершине
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Очередь с приоритетами (мин-куча)

		dist[source] = 0;	  // Расстояние от начальной вершины до самой себя равно 0
		pq.push({0, source}); // Добавляем начальную вершину в очередь

		while (!pq.empty())
		{
			int cur_vertex = pq.top().second;
			int cur_dist = pq.top().first;
			pq.pop();

			// Если текущее расстояние больше, чем сохраненное в dist, игнорируем эту вершину
			if (cur_dist > dist[cur_vertex])
			{
				continue;
			}

			// Обходим соседей текущей вершины
			for (int i = 0; i < n; ++i)
			{
				if (_matrix[cur_vertex][i] != 0)
				{
					int new_dist = dist[cur_vertex] + _matrix[cur_vertex][i];

					// Если новое расстояние меньше текущего сохраненного расстояния до вершины i
					if (new_dist < dist[i])
					{
						dist[i] = new_dist;
						parent[i] = cur_vertex;
						pq.push({new_dist, i});
					}
				}
			}
		}

		// Восстанавливаем путь от вершины target до вершины source
		list<int> path;

		for (int cur = target; cur != -1; cur = parent[cur])
			path.push_front(cur);

		return path;
	}

	// Минимального остовное дерево на основе алгоритма Прима
	// Возвращает: граф, описывающий это дерево
	Graph getSpanningPrime() const
	{
		int vertices = _matrix.size();
		Graph tree(vertices);

		list<Edge> edges;					// рассматриваемые ребра
		vector<bool> used(vertices, false); // использованные вершины

		tree._matrix.resize(vertices);

		used[0] = true; // Начнём с вершины 0.
		for (int i = 0; i < vertices; i++)
		{
			if (_matrix[0][i] > 0)
				edges.push_back(Edge(0, i));

			tree._matrix[i].resize(vertices);
		}

		while (!edges.empty())
		{
			list<Edge>::iterator min_it = edges.begin(), it = edges.begin();

			int min_weight = _matrix[it->_from][it->_to];

			for (; it != edges.end(); it++)
			{
				int weight = _matrix[it->_from][it->_to];

				if (weight != 0 && weight < min_weight)
				{
					min_it = it;
					min_weight = weight;
				}
			}

			Edge min_edge = *min_it;
			edges.erase(min_it);

			if (used[min_edge._to])
				continue;

			used[min_edge._to] = true;
			tree._matrix[min_edge._from][min_edge._to] = _matrix[min_edge._from][min_edge._to];
			tree._matrix[min_edge._to][min_edge._from] = _matrix[min_edge._to][min_edge._from];

			for (int i = 0; i < vertices; i++)
				if (_matrix[min_edge._to][i] > 0 && !used[i])
					edges.push_back(Edge(min_edge._to, i));
		}

		return tree;
	}

	// Минимального остовное дерево на основе алгоритма Крускала
	// Возвращает: граф, описывающий это дерево
	Graph getSpanningKruskal() const
	{
		int vertices = _matrix.size();
		Graph tree(vertices);

		// Создаем приоритетную очередь для ребер, сортированную по весу
		priority_queue<Edge, vector<Edge>, function<bool(Edge, Edge)>> pq(
			[this](const Edge &a, const Edge &b)
			{
				return _matrix[a._from][a._to] > _matrix[b._from][b._to];
			});

		// Добавляем все ребра в приоритетную очередь
		for (int i = 0; i < vertices; ++i)
		{
			for (int j = i + 1; j < vertices; ++j)
			{
				if (_matrix[i][j] > 0)
					pq.push(Edge(i, j));
			}
		}

		// Создаем вектор для хранения номера компонент связности
		vector<int> component(vertices);

		// Инициализируем каждую вершину отдельной компонентой
		for (int i = 0; i < vertices; ++i)
			component[i] = i;

		// Проходим по приоритетной очереди и добавляем ребра в остовное дерево, если они не образуют цикл
		while (!pq.empty())
		{
			Edge edge = pq.top();
			pq.pop();

			int componentFrom = component[edge._from];
			int componentTo = component[edge._to];

			// Если вершины ребра принадлежат разным компонентам связности, добавляем ребро в остовное дерево
			if (componentFrom != componentTo)
			{
				tree._matrix[edge._from][edge._to] = tree._matrix[edge._to][edge._from] = _matrix[edge._from][edge._to];

				// Объединяем компоненты связности
				for (int i = 0; i < vertices; ++i)
					if (component[i] == componentTo)
						component[i] = componentFrom;
			}
		}

		return tree;
	}

	// Получить количество вершин
	int getVertices() const { return _matrix.size(); }

	// Оператор присваивания
	Graph &operator=(const Graph &graph)
	{
		_matrix = graph._matrix;

		return *this;
	}

	// Оператор вывода в консоль
	friend ostream &operator<<(ostream &stream, const Graph &graph)
	{
		int size = graph._matrix.size();

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
				stream << graph._matrix[i][j] << '\t';

			stream << '\n';
		}

		return stream;
	}

	// Оператор вывода в файл
	friend ofstream &operator<<(ofstream &stream, const Graph &graph)
	{
		stream << graph._matrix.size() << ' ';

		for (int i = 0; i < graph._matrix.size(); i++)
			for (int j = i + 1; j < graph._matrix.size(); j++)
				stream << graph._matrix[i][j] << ' ';

		return stream;
	}

	// Оператор ввода из файла
	friend ifstream &operator>>(ifstream &stream, Graph &graph)
	{
		int vertices;

		stream >> vertices;

		if (graph._matrix.size() != vertices)
			graph._matrix.resize(vertices);

		for (int i = 0; i < vertices; i++)
		{
			if (graph._matrix[i].size() != vertices)
				graph._matrix[i].resize(vertices);

			for (int j = i + 1; j < vertices; j++)
			{
				stream >> graph._matrix[i][j];

				graph._matrix[j][i] = graph._matrix[i][j];
			}
		}

		return stream;
	}

	~Graph() {}
};

int main(int argc, char *argv[])
{
	// Создаём граф на основе матрицы смежности
	Graph graph_old({{0, 0, 0, 7, 6, 0, 1, 4, 4, 5, 6, 6, 7},
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
					 {7, 2, 5, 8, 0, 6, 8, 2, 1, 7, 6, 5, 0}});

	ofstream out_file("graph.txt");

	// Записываем граф в файл
	out_file << graph_old;

	out_file.close();

	ifstream in_file("graph.txt");

	Graph graph(13);

	// Читаем граф из файла
	in_file >> graph;

	in_file.close();

	// Выводим граф
	cout << graph;

	// Находим и выводим минимальное остовное дерево по алгоритму Прима
	Graph prime = graph.getSpanningPrime();
	cout << "Prime:\n"
		 << prime;

	// Находим и выводим минимальное остовное дерево по алгоритму Крускала
	Graph kruskal = graph.getSpanningKruskal();
	cout << "Kruskal:\n"
		 << kruskal;

	// Находим путь 0 -> 9
	list<int> path = prime.findPath(0, 9);

	// Выводим путь
	for (int v : path)
		cout << v << " -> ";

	cout << endl;

	return 0;
}