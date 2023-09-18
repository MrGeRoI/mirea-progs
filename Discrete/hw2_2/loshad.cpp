#include <iostream>

using namespace std;

void dfs(bool **matrix,bool *valid,int number,int count)
{
	valid[number] = true;

	for(int i = 0; i < count; i++)
		if(matrix[number][i] && !valid[i])
			dfs(matrix,valid,i,count);
}

int main(int argc, char* argv[])
{
	int count, number;

	cin >> count >> number;

	number--;

	bool **matrix = new bool*[count], *valid = new bool[count];

	for(int i = 0; i < count; i++)
	{
		matrix[i] = new bool[count];

		valid[i] = false;
		
		for(int j = 0; j < count; j++)
			matrix[i][j] = false;
	}

	while(true)
	{
		int x; cin >> x;

		if(x == 0)
			break;

		x--;

		int y; cin >> y; y--;

		matrix[x][y] = true;
	}
		
	dfs(matrix,valid,number,count);

	valid[number] = true;

	for(int i = 0; i < count; i++)
		if(!valid[i])
		{
			cout << "No" << endl;
			return 0;
		}

	cout << "Yes" << endl;	
	return 0;
}