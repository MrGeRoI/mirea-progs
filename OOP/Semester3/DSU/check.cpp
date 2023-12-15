#include <chrono>
#include <iostream>
#include <fstream>
#include <queue>
#include <random>
#include <algorithm>

#include "dermo.hpp"
#include "unordered_dsu.hpp"

#define TEST_N 1 // 1 2 3 4 5

using namespace std;

int main(int argc, char *argv[])
{
	random_device rd;
	mt19937 g(rd());

	int test_size = 500;

	list<pair<int, int>> query1, query2;

	vector<int> numbers1, numbers2;

	while (true)
	{
		uniform_int_distribution<int> distribution(0, test_size - 1);

		query1.clear();
		query2.clear();

		numbers1.clear();
		numbers2.clear();

		for (int i = 0; i < test_size; i++)
		{
			numbers1.push_back(i);
			numbers2.push_back(i);
		}

		shuffle(numbers1.begin(), numbers1.end(), g);
		shuffle(numbers2.begin(), numbers2.end(), g);

		while (!numbers1.empty())
		{
			query1.push_back(pair<int, int>(numbers1.back(), distribution(g)));
			query2.push_back(pair<int, int>(numbers2.back(), distribution(g)));

			numbers1.pop_back();
			numbers2.pop_back();
		}

#if TEST_N == 1
		dsu_1 ex1(test_size);
#elif TEST_N == 2
		dsu_2 ex2;
#elif TEST_N == 3
		dsu_3 ex3(test_size);
#elif TEST_N == 4
		dsu ex4(test_size);
#elif TEST_N == 5
		unordered_dsu ex5(test_size);
#endif

		auto begin = chrono::steady_clock::now();

		while (!query1.empty())
		{
			pair<int, int> q = query1.front();

#if TEST_N == 1
			ex1.unite(q.first, q.second);
#elif TEST_N == 2
			ex2.make_set(q.first);
			ex2.make_set(q.second);
			ex2.unite(q.first, q.second);
#elif TEST_N == 3
			ex3.follow(q.first, q.second);
#elif TEST_N == 4
			ex4.follow(q.first, q.second);
#elif TEST_N == 5
			ex5.unite(q.first, q.second);
#endif

			query1.pop_front();

			q = query2.front();

#if TEST_N == 1
			ex1.equal(q.first, q.second);
#elif TEST_N == 2
			ex2.equal(q.first, q.second);
#elif TEST_N == 3
			ex3.equal(q.first, q.second);
#elif TEST_N == 4
			ex4.equal(q.first, q.second);
#elif TEST_N == 5
			ex5.equal(q.first, q.second);
#endif

			query2.pop_front();
		}

		auto end = chrono::steady_clock::now();
		int len = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

		cout << "Elapsed " << test_size << ": " << len << " ms\n";

		ofstream file(string("dsu.csv"), ios::app);
		file << TEST_N << ',' << test_size << ',' << len << '\n';
		file.close();

		test_size %= 5000;
		test_size += 500;
	}

	return 0;
}