#include <iostream>

#define DIRT -1
#define EMPTY 0
#define GARDEN 1
 
using namespace std;

void bfs(int **matrix,int x,int y,int w,int h)
{
    matrix[x][y] = GARDEN;
 
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
	int garden = 0;
	int n, m;

	cin >> n >> m;

	int **matrix = new int*[n];

	for(int i = 0; i < n; i++)
	{
		matrix[i] = new int[m];

		for(int j = 0;j < m;j++)
			matrix[i][j] = EMPTY;
	}

	for(int i = 0;i < n;i++)
	for(int j = 0;j < m;j++)
	{
		char c; cin >> c;

		if(c == '.')
			matrix[i][j] = DIRT;
	}
	
	for(int i = 0;i < n;i++)
	for(int j = 0;j < m;j++)
	{
		if(matrix[i][j] == EMPTY)
		{
			garden++;
			bfs(matrix, i, j, n, m);
		}
	}

	cout << garden << endl;

	return 0;
}