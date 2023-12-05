#include <iostream>

#include "lca.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	lca a(100);

	a.joint(0, 1);
	a.joint(2, 1);

	a.scan();

	cout << a.find(0, 2) << endl;

	return 0;
}