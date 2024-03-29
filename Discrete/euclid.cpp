﻿#include <iostream>
#include <fstream>
#include <algorithm>

/* https://acmp.ru/index.asp?main=task&id_task=527
	Дима недавно начал изучать информатику. Одним из первых алгоритмов, который он изучил, был алгоритм Евклида для нахождения наибольшего общего делителя (НОД) двух чисел. Напомним, что наибольшим общим делителем двух чисел a и b называется наибольшее натуральное число x, такое, что и число a, и число b делится на него без остатка.

	Алгоритм Евклида заключается в следующем:

	Пусть a, b – числа, НОД которых надо найти.
	Если b = 0, то число a – искомый НОД.
	Если b > a, то необходимо поменять местами числа a и b.
	Присвоить числу a значение a – b.
	Вернуться к шагу 2.
	Дима достаточно быстро освоил алгоритм Евклида и вычислил с его помощью много наибольших общих делителей. Поняв, что надо дальше совершенствоваться, ему пришла идея решить новую задачу. Пусть заданы числа a, b, c и d. Требуется узнать, наступит ли в процессе реализации алгоритма Евклида для заданной пары чисел (a, b) такой момент, когда число a будет равно c, а число b будет равно d.

	Требуется написать программу, которая решает эту задачу.
*/

// a , b - пара исходных чисел
// c , d - пара чисел в серии чисел алгоритма евклида
// return: наличие пары c , d в алгоритме евклида для чисел a , b
bool euclid(long long a,long long b,const long long c,const long long d)
{
	if(a == c && b == d)
		return true;

	while(b)
	{
		if(b > a)
			std::swap(a,b);
	
		if(b)
		{
			if(c > a)
				return false;

			// оптимизация алгоритма (множественные вычитания --> одно деление)
			a -= (a / b) * b;

			if(c % b == a && d == b )
				return true;
		}
		else if(a == c && b == d)
				return true;
	}
	
	return false;
}

int main(int argc, char* argv[])
{
	std::ifstream input("input.txt");

	std::ofstream output("output.txt");

	int k;

	input >> k;

	for(int i = 0;i < k;i++)
	{
		long long a,b,c,d;

		input >> a >> b >> c >> d;

		output << ( euclid(a,b,c,d) ? "YES" : "NO" ) << std::endl;
	}

	input.close();

	output.close();

    return 0;
}
