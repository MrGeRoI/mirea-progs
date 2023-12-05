
#include <iostream>
#include <queue>
#include <stack>
#include <list>

using namespace std;

bool hamilton(vector<vector<int> >& mat, vector <bool>& visited, vector <int>& path, int curr)
{
	path.push_back(curr);
	//путь содержит все вершины: если есть связь последней вершины с исходной, цикл найден
	//если нет, откатываемся на шаг назад
	cout << "\n";
	for(int i=0; i < path.size(); i++) cout << path[i] << " ";
	//вершина использована в пути
	visited[curr] = true;
	//проверить всех непосещенных соседей вершины curr
	//if (path.size() == mat[0].size()) return true; //mat.size()
	if (path.size() == mat[0].size() && mat[path[path.size() - 1]][path[0]] != 0) return true;
	if (path.size() == mat[0].size() && mat[path[path.size() - 1]][path[0]] == 0)
	{
		visited[curr] = false;
		path.pop_back();
		return false;
	}

	for (int i = 0; i < mat[0].size(); i++)
	{
		if (mat[curr][i] > 0 && !visited[i])
			if (hamilton(mat, visited, path, i)) return true;
	}

	//этот путь не подходит, убираем вершину и откатываемся
	visited[curr] = false;
	path.pop_back();
	return false;
}

int main()
{
	vector<vector<int> > mat =
	{
	{ 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 1 },
	{ 0, 1, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 1, 0, 1 },
	{ 0, 1, 0, 0, 1, 0 }
	};
	vector<bool> visited(6, 0);
	vector<int> path;

	for (int i = mat[0].size()-1; i >=0; i--)
	{
		if (hamilton(mat, visited, path, i))
		{
			cout << "\ntrue"; 
			break;
		}
		else
		{
			path.clear();
			for (int j = 0; j < mat[0].size(); j++) visited[j] = 0;
		}
	}
		
		
	//cout << "\nHamilton: " << hamilton(mat, visited, path, 3);

	return 0;
}