#include <iostream>

#define IMMUE -1
#define EMPTY 0
#define VIRUS 1

using namespace std;

void bfs(int **matrix,int x,int y,int w,int h)
{
	matrix[x][y] = VIRUS;

	if(x > 0 && matrix[x - 1][y] == EMPTY)
		bfs(matrix,x - 1,y,w,h);
		
	if(y > 0 && matrix[x][y - 1] == EMPTY)
		bfs(matrix,x,y - 1,w,h);
		
	if(x < w - 1 && matrix[x + 1][y] == EMPTY)
		bfs(matrix,x + 1,y,w,h);
		
	if(y < h - 1 && matrix[x][y + 1] == EMPTY)
		bfs(matrix,x,y + 1,w,h);
}

int main(int argc, char* argv[])
{
	int virus = 0;
	int n, m, k;

	cin >> n >> m >> k;

	int **matrix = new int*[n];

	for(int i = 0; i < n; i++)
	{
		matrix[i] = new int[m];

		for(int j = 0;j < m;j++)
			matrix[i][j] = EMPTY;
	}

	for(int i = 0; i < k; i++)
	{
		int x, y; cin >> x >> y; x--; y--;
		matrix[x][y] = IMMUE;
	}
	
	for(int i = 0;i < n;i++)
	for(int j = 0;j < m;j++)
	{
		if(matrix[i][j] == EMPTY)
		{
			virus++;
			bfs(matrix, i, j, n, m);
		}
	}

	cout << virus << endl;

	return 0;
}