#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct Flight
{
public:
	double lenght;
	int price;

	Flight(double len = 0.0, int pr = 0)
	{
		lenght = len;
		price = pr;
	}

	bool operator>(const Flight &flight)
	{
		if (lenght == flight.lenght)
			return price > flight.price;

		return lenght > flight.lenght;
	}

	bool operator<(const Flight &flight)
	{
		if (lenght == flight.lenght)
			return price < flight.price;

		return lenght < flight.lenght;
	}

	bool operator==(const Flight &flight)
	{
		return lenght == flight.lenght && price == flight.price;
	}
};

class Aviacompany
{
private:
	vector<vector<Flight>> matrix;

public:
	Aviacompany(int points) : matrix(points)
	{
		for (int i = 0; i < points; i++)
			matrix[i].resize(points);
	}

	Aviacompany(vector<vector<Flight>> flights) : matrix(flights) {}

	list<int> getBestPath(int start, int to)
	{
		int n = matrix.size();

		// Массив для хранения времени до каждой вершины
		vector<double> time(n, 1000000.0);

		// Приоритетная очередь для хранения вершин с наименьшим временем
		priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

		// Инициализация начальной вершины
		time[start] = 0;
		pq.push({0, start});

		// Массив для хранения предыдущей вершины
		vector<int> prev(n, -1);

		while (!pq.empty())
		{
			int u = pq.top().second;
			pq.pop();

			// Обход смежных вершин
			for (int v = 0; v < n; ++v)
			{
				if (matrix[u][v].lenght > 0) // Проверка наличия рейса между вершинами
				{
					double newTime = time[u] + matrix[u][v].lenght;

					// Обновление времени до вершины, если найден более короткий путь
					if (newTime < time[v])
					{
						time[v] = newTime;
						prev[v] = u;
						pq.push({time[v], v});
					}
				}
			}
		}

		// Восстановление пути
		list<int> path;
		for (int v = to; v != -1; v = prev[v])
			path.push_back(v);

		return path;
	}
};

int main(int argc, char *argv[])
{
	Aviacompany avia({{Flight(), Flight(2.6, 3), Flight(53.0, 3)},
					  {Flight(5.0, 3), Flight(), Flight(2.4, 3)},
					  {Flight(52.3, 3), Flight(3.12, 3), Flight()}});

	for (int n : avia.getBestPath(0, 2))
	{
		cout << n << "<-";
	}

	cout << endl;
}