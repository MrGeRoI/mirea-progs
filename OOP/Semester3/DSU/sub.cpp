#include <iostream>

#include "sub.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	sub<char> str(100);

	vector<tuple<int, int, char>> query = {
		// Конец C-строки
		{99, 100, '\0'},

		{14, 15, '*'},
		{13, 19, '\\'},
		{5, 19, '\\'},

		{94, 95, '!'},
		{93, 96, '.'},

		{13, 50, '#'},
		{20, 52, '#'},

		// Оставшиеся ячейки закрасить нижними подчёркиваниями
		{0, 100, '_'}};

	for (tuple<int, int, char> q : query)
	{
		cout << "Fill (" << get<0>(q) << ", " << get<1>(q) << "): " << get<2>(q) << endl;

		str.fill(get<0>(q), get<1>(q), get<2>(q));
	}

	cout << "Sub: " << str.values().data() << endl;

	return 0;
}