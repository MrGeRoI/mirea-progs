#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <queue>
#include <functional>

#include <cmath>

const int MNOGO = 10000;

using namespace std;

using matrix = vector<vector<int>>;

template <class T>
void push(list<T> &container, T value)
{
	container.push_back(value);
}

template <class T>
void remove(list<T> &container, T value)
{
	for (typename list<T>::iterator it = container.begin(); it != container.end(); it++)
	{
		container.erase(it);
		return;
	}
}

template <class T>
vector<T> greater_(const list<T> &container, typename list<T>::const_iterator it)
{
	vector<T> result;

	T minimum = *it;

	for (it = container.begin(); it != container.end(); it++)
		if (*it > minimum)
			result.push_back(*it);

	return result;
}

int find_path(const matrix &graph, matrix &total_flow, int source, int destination) // source - исток, destination - сток
{
	int cur_vertex, vertices = graph.size();

	vector<int> flow(vertices);
	fill(flow.begin(), flow.end(), 0);
	vector<int> link(vertices);
	fill(flow.begin(), flow.end(), -1);
	flow[source] = MNOGO;
	vector<bool> used(vertices, false);

	priority_queue<int, vector<int>, function<bool(int, int)>> vertex([flow](int x, int y)
																	  { return flow[x] < flow[y]; });

	vertex.push(source);

	while (!vertex.empty())
	{
		int v = vertex.top();

		if (v == destination)
			break;

		vertex.pop();

		for (int i = 0; i < vertices; i++)
			if (graph[v][i] - total_flow[v][i] > 0 && !used[i])
			{
				flow[i] = (graph[v][i] - total_flow[v][i] < flow[v]) ? graph[v][i] - total_flow[v][i] : flow[v];
				link[i] = v;

				vertex.push(i);
			}

		used[v] = true;
	}

	if (link[destination] == -1)
		return 0;

	cur_vertex = destination;

	while (cur_vertex != source)
	{
		total_flow[link[cur_vertex]][cur_vertex] += flow[destination];
		cur_vertex = link[cur_vertex];
	}

	return flow[destination];
}

int max_flow(const matrix &graph, matrix &flow, int source, int destination)
{
	int vertices = graph.size();

	flow.resize(vertices);

	for (int i = 0; i < flow.size(); i++)
	{
		flow[i].resize(graph[i].size());
		fill(flow[i].begin(), flow[i].end(), 0);
	}

	int max_flow = 0, add_flow;
	do
	{
		add_flow = find_path(graph, flow, source, destination);
		max_flow += add_flow;
	} while (add_flow > 0);

	return max_flow;
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

template <class T>
void print(const list<T> &container)
{
	for (typename list<T>::const_iterator it = container.begin(); it != container.end(); it++)
		cout << *it << ' ';
}

template <class T>
void print(const vector<T> &container)
{
	for (int i = 0; i < container.size(); i++)
		cout << container[i] << ' ';
}

int main()
{
	list<int> numbers;

	for (int i = 0; i < 20; i++)
		push(numbers, int(20 + sin(double(i)) * 20));

	typename list<int>::const_iterator it = numbers.begin();
	it++;
	it++;
	it++;
	it++;
	it++;
	it++;

	cout << "Numbers: ";

	print(numbers);

	cout << endl;

	cout << "Greater than " << *it << ": ";

	print(greater_(numbers, it));

	cout << endl;

	matrix graph = {{0, 5, 2, 7, 4, 8, 8, 8, 0, 6, 8, 4},
					{5, 0, 7, 2, 0, 8, 9, 6, 4, 2, 5, 4},
					{2, 7, 0, 1, 3, 3, 8, 3, 2, 6, 3, 6},
					{7, 2, 1, 0, 6, 8, 0, 6, 3, 9, 4, 3},
					{4, 0, 3, 6, 0, 9, 2, 3, 5, 9, 6, 8},
					{8, 8, 3, 8, 9, 0, 9, 5, 4, 6, 9, 1},
					{8, 9, 8, 0, 2, 9, 0, 0, 0, 5, 5, 8},
					{8, 6, 3, 6, 3, 5, 0, 0, 0, 7, 6, 3},
					{0, 4, 2, 3, 5, 4, 0, 0, 0, 6, 5, 4},
					{6, 2, 6, 9, 9, 6, 5, 7, 6, 0, 8, 1},
					{8, 5, 3, 4, 6, 9, 5, 6, 5, 8, 0, 9},
					{4, 4, 6, 3, 8, 1, 8, 3, 4, 1, 9, 0}},
		   flow;

	print(graph);

	// Максимальный поток: 45
	cout << "Max flow: " << max_flow(graph, flow, 0, graph.size() - 1) << endl;

	print(flow);

	return 0;
}
