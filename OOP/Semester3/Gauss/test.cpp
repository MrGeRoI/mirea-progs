#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Flight
{
public:
	int lenght;
	int price;

	Flight(int len = 0.0, int pr = 0)
	{
		lenght = len;
		price = pr;
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

	int edjes()
	{
		int n = matrix.size();
		int e = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (matrix[i][j].price != 0)
					e++;
			}
		}
		return e;
	}

	vector<vector<int>> WeightedList()
	{
		vector<vector<int>> weightedList(edjes());
		int n = 0;
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = i + 1; j < matrix[i].size(); j++)
			{
				if (matrix[i][j].price != 0)
				{
					weightedList[n].push_back(i);
					weightedList[n].push_back(j);
					weightedList[n].push_back(matrix[i][j].price);
					n++;
				}
			}
		}
		return weightedList;
	}

	vector<vector<int>> OrientWeightedList()
	{
		vector<vector<int>> weightedList(edjes());
		int n = 0;
		for (int i = 0; i < matrix.size(); i++)
		{
			for (int j = 0; j < matrix[i].size(); j++)
			{
				if (matrix[i][j].lenght != 0)
				{
					weightedList[n].push_back(i);
					weightedList[n].push_back(j);
					weightedList[n].push_back(matrix[i][j].lenght);
					n++;
				}
			}
		}
		return weightedList;
	}

	vector<int> BellmanFord(vector<vector<int>> graph, int start)
	{
		// инициализируем расстояние до всех вершин
		int v = matrix.size();
		int e = edjes();

		vector<int> dis(v, 100000);
		// инициализируем начальную вершину
		dis[start] = 0;
		for (int i = 0; i < v - 1; i++)
		{
			for (int j = 0; j < e; j++)
			{
				if (dis[graph[j][0]] != 1000000 && dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
					dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
			}
		}
		for (int i = 0; i < e; i++)
		{
			int x = graph[i][0];
			int y = graph[i][1];
			int weight = graph[i][2];
			if (dis[x] != 1000000 && dis[x] + weight < dis[y])
				cout << "Negative weight cycle" << endl;
		}
		return dis;
	}
	friend ostream &operator<<(ostream &stream, const Flight &flight);
};
ostream &operator<<(ostream &stream, const Flight &flight)
{
	stream << flight.lenght << ' ' << flight.price;
	return stream;
}

void print(const vector<int> &a)
{
	for (int x : a)
		cout << x << ' ';
	cout << '\n';
}

int main(int argc, char *argv[])
{
	Aviacompany avia({{Flight(), Flight(7, 7), Flight(9, 0), Flight(0, 0), Flight(0, 4), Flight(14, 0)},
					  {Flight(7, 7), Flight(), Flight(10, 5), Flight(15, 0), Flight(0, 0), Flight(0, 2)},
					  {Flight(9, 0), Flight(10, 5), Flight(), Flight(11, 11), Flight(0, 0), Flight(2, 6)},
					  {Flight(0, 0), Flight(15, 0), Flight(11, 11), Flight(), Flight(6, 8), Flight(0, 9)},
					  {Flight(0, 4), Flight(0, 0), Flight(0, 0), Flight(6, 8), Flight(), Flight(9, 3)},
					  {Flight(14, 0), Flight(0, 2), Flight(2, 6), Flight(0, 9), Flight(9, 3), Flight()}});

	Aviacompany avia2({
		{Flight(), Flight(4, 7), Flight(5, 0), Flight(0, 0)},
		{Flight(0, 7), Flight(), Flight(0, 5), Flight(0, 0)},
		{Flight(0, 0), Flight(0, 5), Flight(), Flight(3, 11)},
		{Flight(0, 0), Flight(-10, 0), Flight(0, 11), Flight()},
	});
	Aviacompany avia3({
		{Flight(), Flight(4, 7), Flight(5, 0), Flight(0, 0)},
		{Flight(0, 7), Flight(), Flight(5, 5), Flight(0, 0)},
		{Flight(0, 0), Flight(0, 5), Flight(), Flight(3, 11)},
		{Flight(0, 0), Flight(-10, 0), Flight(0, 11), Flight()},
	});

	vector<vector<int>> weightedList = avia2.OrientWeightedList();
	for (int i = 0; i < weightedList.size(); i++)
	{
		print(weightedList[i]);
	}

	vector<vector<int>> weightedList2 = avia3.OrientWeightedList();
	for (int i = 0; i < weightedList2.size(); i++)
	{
		print(weightedList2[i]);
	}

	print(avia2.BellmanFord(weightedList, 0));
	print(avia3.BellmanFord(weightedList2, 0));

	cout << endl;
}