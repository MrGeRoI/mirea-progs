#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int n,s,f;

	cin >> n >> s >> f;

	s--; f--;

	int *dist = new int[n],**matrix = new int*[n];
	bool *visited = new bool[n];

	for(int i = 0; i < n; i++)
	{
		matrix[i] = new int[n];

		dist[i] = -1; // (-1) - аналог бесконечности
		
		visited[i] = false;

		for(int j = 0; j < n; j++)
			cin >> matrix[i][j];
	}
	
	dist[s] = 0;

	int index,minimum;

	do
	{
		index = -1;
		minimum = 10000; // Макс вершин (100) * макс вес (100) = макс длина пути (10'000)

		for(int i = 0; i < n; i++)
		{
			if(!visited[i] && dist[i] >= 0 && dist[i] < minimum)
			{
				minimum = dist[i];
				index = i;
			}
		}

		if(index >= 0)
		{
			for(int i = 0;i < n;i++)
			{
				if(matrix[index][i] < 0)
					continue;
				
				int d = minimum + matrix[index][i];

				if(dist[i] < 0 || d < dist[i])
					dist[i] = d;
			}

			visited[index] = true;
		}
	}
	while(index != -1);

	cout << dist[f] << endl;

	return 0;
}