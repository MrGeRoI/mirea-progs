#include <iostream>

#include "dsu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	dsu some(100);

	some.unite(2,3);

	some.equal(2,3);

	return 0;
}