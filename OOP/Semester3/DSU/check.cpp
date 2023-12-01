#include <chrono>
#include <iostream>
#include <queue>
#include <random>
#include <algorithm>

#include "dermo.hpp"
#include "unordered_dsu.hpp"

const int TEST_SIZE = 5000;

using namespace std;

int main(int argc, char *argv[])
{
	list<pair<int, int>> query1;
	list<pair<int, int>> query2;

	vector<int> numbers1;
	vector<int> numbers2;
	for (int i = 0; i < TEST_SIZE; i++)
	{
		numbers1.push_back(i);
		numbers2.push_back(i);
	}

	random_device rd;
	mt19937 g(rd());

	uniform_int_distribution<int> distribution(0, TEST_SIZE - 1);

	shuffle(numbers1.begin(), numbers1.end(), g);
	shuffle(numbers2.begin(), numbers2.end(), g);

	while (!numbers1.empty())
	{
		query1.push_back(pair<int, int>(numbers1.back(), distribution(g)));
		query2.push_back(pair<int, int>(numbers2.back(), distribution(g)));

		numbers1.pop_back();
		numbers2.pop_back();
	}

	//dsu_1 ex1(TEST_SIZE);
	//dsu_2 ex2;
	//dsu_3 ex3(TEST_SIZE);
	dsu ex4(TEST_SIZE);
	//unordered_dsu ex5(TEST_SIZE);

	auto begin = chrono::steady_clock::now();

	while (!query1.empty())
	{
		pair<int, int> q = query1.front();

		//ex1.unite(q.first, q.second);

		//ex2.make_set(q.first);
		//ex2.make_set(q.second);
		//ex2.unite(q.first,q.second);

		//ex3.follow(q.first,q.second);

		ex4.follow(q.first,q.second);

		//ex5.unite(q.first,q.second);

		query1.pop_front();
	}

	auto end = chrono::steady_clock::now();
	int len = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	cout << "Fill: " << len << " ms\n";

	begin = chrono::steady_clock::now();

	while (!query2.empty())
	{
		pair<int, int> q = query2.front();

		//ex1.equal(q.first, q.second);
		//ex2.equal(q.first,q.second);
		//ex3.equal(q.first,q.second);
		ex4.equal(q.first,q.second);
		//ex5.equal(q.first,q.second);

		query2.pop_front();
	}

	end = chrono::steady_clock::now();
	len = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

	cout << "Find: " << len << " ms\n";

	return 0;
}