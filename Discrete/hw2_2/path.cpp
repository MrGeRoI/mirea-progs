#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int count, start, end;

	cin >> count;

	bool *visited = new bool[count],**matrix = new bool*[count];
	int *dist = new int[count];
	
	for(int i = 0; i < count; i++)
	{
		matrix[i] = new bool[count];

		dist[i] = -1;
		
		visited[i] = false;

		for(int j = 0; j < count; j++)
			cin >> matrix[i][j];
	}

	cin >> start >> end;

	start--; end--;
	
	dist[start] = 0;

	int index, minimum;

	do
	{
		index = -1;
		minimum = 100;

		for(int i = 0; i < count; i++)
		{
			if(!visited[i] && dist[i] >= 0 && dist[i] < minimum)
			{
				minimum = dist[i];
				index = i;
			}
		}

		if(index >= 0)
		{
			for(int i = 0;i < count;i++)
			{
				if(matrix[index][i] && (dist[i] < 0 || minimum + 1 < dist[i]))
					dist[i] = minimum + 1;
			}

			visited[index] = true;
		}
	}
	while(index != -1);

	cout << dist[end] << endl;

	return 0;
}