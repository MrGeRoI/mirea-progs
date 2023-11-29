#include <iostream>

#include "mapped_dsu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	dsu some(100);

	some.unite(2, 3);

	cout << (some.equal(2, 3) ? "Yes" : "No") << ", " << some.count(2) << endl;

	mapped_dsu<std::string> str;
	str.make_set("");

	return 0;
}