#include <iostream>

using namespace std;

#define IBV(i,b,v) (((i) << 2) | ((b) << 1) | (v))

#define I(x) (((x) >> 2) & 1)
#define B(x) (((x) >> 1) & 1)
#define V(x) ((x) & 1)

#define INDIGO (1 << 2)
#define BLUE (1 << 1)
#define VIOLET (1)

int max_indigo(bool **matrix,int count,int *colours,int color,int index,int parent)
{
	if(colours[index] & color == 0)
		return -1;

	int lamps = (color == INDIGO) ? 1 : 0;

	for(int i = 0; i < count; i++)
	{
		if(i != parent && matrix[index][i])
		{
			if(color == INDIGO)
				lamps += (std::max)(
					max_indigo(matrix,count,colours,BLUE,i,index),
					max_indigo(matrix,count,colours,VIOLET,i,index)
				);
			else if(color == BLUE)
				lamps += (std::max)(
					max_indigo(matrix,count,colours,INDIGO,i,index),
					max_indigo(matrix,count,colours,VIOLET,i,index)
				);
			else if(color == VIOLET)
				lamps += (std::max)(
					max_indigo(matrix,count,colours,INDIGO,i,index),
					max_indigo(matrix,count,colours,BLUE,i,index)
				);
		}
	}

	return lamps;
}

int main(int argc, char* argv[])
{
	int n;

	cin >> n;

	bool **matrix = new bool*[n];
	int *colours = new int[n];

	for(int i = 0; i < n; i++)
	{
		matrix[i] = new bool[n];

		for(int j = 0;j < n;j++)
			matrix[i][j] = false;
	}

	for(int i = 0; i < (n - 1); i++)
	{
		int u,v; cin >> u >> v; u--; v--;
	
		matrix[u][v] = matrix[v][u] = true;
	}

	for(int i = 0; i < n; i++)
	{
		char c[3]; cin >> c;
	
		colours[i] = IBV(
			(int)(c[0] == 'I' || c[1] == 'I' || c[2] == 'I'),
			(int)(c[0] == 'B' || c[1] == 'B' || c[2] == 'B'),
			(int)(c[0] == 'V' || c[1] == 'V' || c[2] == 'V')
		);
	}

	cout << (std::max)(
		max_indigo(matrix,n,colours,INDIGO,0,-1),
		(std::max)(
			max_indigo(matrix,n,colours,BLUE,0,-1),
			max_indigo(matrix,n,colours,VIOLET,0,-1)
		)
	) << endl;

    return 0;
}