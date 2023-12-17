#include <iostream>

#include "lca.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	lca tree(100);

	vector<pair<int, int>> query = {
		{5, 4},
		{6, 4},
		{7, 4},

		{8, 1},
		{9, 1},

		{10, 2},
		{11, 2},

		{12, 3},
		{13, 3},

		{1, 0},
		{2, 0},
		{3, 0},
		{4, 0}};

	for (pair<int, int> q : query)
	{
		cout << "Joint: " << q.first << ' ' << q.second << endl;
		tree.joint(q.first, q.second);
	}

	tree.scan(0);

	cout << "LCA(5,9): " << tree.find(5, 9) << endl;

	cout << "LCA(8,9): " << tree.find(8, 9) << endl;

	return 0;
}