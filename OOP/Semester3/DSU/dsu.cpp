#include <iostream>

#include "mapped_dsu.hpp"

#include "unordered_dsu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	dsu some(100);

	some.follow(2, 3);
	some.follow(3, 6);
	some.follow(4, 6);

	cout << some.find(2) << endl;

	unordered_dsu nums(10);

	nums.unite(1, 2);
	nums.unite(2, 3);
	nums.unite(3, 4);

	nums.unite(6, 5);
	nums.unite(7, 6);
	nums.unite(8, 7);
	nums.unite(9, 8);

	cout << "(1,4): " << nums.equal(1, 4) << endl
		 << "(6,9): " << nums.equal(6, 9) << endl
		 << "(1,9): " << nums.equal(1, 9) << endl;

	mapped_dsu<std::string> unik;

	unik.make_set("MGU");
	unik.make_set("MIREA");
	unik.make_set("Baumanka");
	unik.make_set("Fiz-Teh");
	unik.make_set("VSHE");

	unik.follow("MGU", "MIREA");
	unik.follow("Baumanka", "MGU");
	unik.follow("Fiz-Teh", "VSHE");

	cout << "Baumanka < " << unik.find("Baumanka") << endl
		 << "Fiz-Teh < " << unik.find("Fiz-Teh") << endl;

	return 0;
}