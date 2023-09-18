#include <iostream>

#define LOSCUT -1
#define EMPTY 0
#define CUT 1
 
using namespace std;

void bfs(int **matrix,int x,int y,int w,int h)
{
	matrix[x][y] = LOSCUT;

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
	int loscut = 0;
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
		cin >> matrix[i][j];
	}
		
	for(int i = 0;i < n;i++)
	for(int j = 0;j < m;j++)
	{
		if(matrix[i][j] == EMPTY)
		{
			loscut++;
			bfs(matrix, i, j, n, m);
		}
	}

	cout << loscut << endl;

	return 0;
}