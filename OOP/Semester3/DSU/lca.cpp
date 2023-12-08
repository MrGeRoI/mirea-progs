#include <iostream>

#include "lca.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	lca a(100);

	a.joint(1, 4);
	a.joint(2, 4);
	a.joint(3, 4);

	a.joint(5, 1);
	a.joint(6, 1);

	a.joint(7, 2);
	a.joint(8, 2);

	a.joint(9, 3);
	a.joint(10, 3);

	a.scan();

	cout << a.find(5, 9) << endl;

	return 0;
}