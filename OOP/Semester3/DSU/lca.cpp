#include <iostream>

#include "lca.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	lca a(100);

	vector<pair<int, int>> query = {
		{1, 4},
		{2, 4},
		{3, 4},

		{5, 1},
		{6, 1},

		{7, 2},
		{8, 2},

		{9, 3},
		{10, 3}};

	for (pair<int, int> q : query)
	{
		cout << "Joint: " << q.first << ' ' << q.second << endl;
		a.joint(q.first, q.second);
	}

	cout << "LCA(5,9): " << a.find(5, 9) << endl;

	return 0;
}