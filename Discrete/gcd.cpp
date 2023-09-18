#include <iostream>
#include <fstream>

/* https://acmp.ru/index.asp?main=task&id_task=148
	Даны два натуральных числа A и B. Требуется найти их наибольший общий делитель (НОД).

	Входные данные
	Во входном файле INPUT.TXT в единственной строке записаны натуральные числа A и B через пробел (A, B ≤ 109).

	Выходные данные
	В выходной файл OUTPUT.TXT выведите НОД чисел А и В.
*/

// из онлайн семинара хд
// m , n - натуральные числа
// return: наибольший общий делитель чисел m и n
int gcd(int m,int n)
{
	int r;

	while(n != 0)
	{
		r = m % n;
		m = n;
		n = r;
	}

	return abs(m);
}

int main(int argc, char* argv[])
{
	std::ifstream input("input.txt");

	int a,b;

	input >> a >> b;

	input.close();

// ====================================== //

	std::ofstream output("output.txt");

	output << gcd(a,b);

	output.close();

    return 0;
}
