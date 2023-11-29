#include <iostream>

#include "sub.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	sub<char> str(100);

	// Конец C-строки
	str.fill(99, 100, '\0');

	str.fill(14, 15, '*');
	str.fill(13, 19, '\\');
	str.fill(5, 19, '\\');

	str.fill(94, 95, '!');
	str.fill(93, 96, '.');

	str.fill(13, 50, '#');
	str.fill(20, 52, '#');
	
	// Оставшиеся ячейки закрасить нижними подчёркиваниями
	str.fill(0, 100, '_');

	cout << str.values().data() << endl;

	return 0;
}