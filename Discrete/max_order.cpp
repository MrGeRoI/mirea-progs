#include <iostream>

// Возведение в степень целого числа
int power(int num,int degree)
{
	if(degree < 1)
		return 1;

	if(degree == 1)
		return num;

	int result = num;

	for(int p = 1;p < degree;p++)
		result *= num;

	return result;
}

// из онлайн семинара хд
// a , b - натуральные числа
// return: наибольший общий делитель чисел a и b
int gcd(int a,int b)
{
	int r;

	while(b != 0)
	{
		r = a % b;
		a = b;
		b = r;
	}

	return abs(a);
}

// a , b - натуральные числа
// return: наименьшее общее кратное чисел a и b
int lcm(int a,int b)
{
	return a*b / gcd(a,b);
}

int main(int argc,char* argv[])
{
	int test[] = {
		61,
		800,
		55450,
		2383254,
		316030564,
		730887505,
		1847653789,
		1478783811,
	};

	for(int n : test)
	{
		int m = n;
		int max_order = 1;

		// Раскладываю модуль кольца вычетов на степени простых чисел
		for(int p = 2;p*p < n;p++)
		{
			int k = 0;

			while(m % p == 0)
			{
				m /= p;
				k++;
			}

			if(k > 0)
			{
				/*
					Для p = 2 наибольший порядок это:
						2^(k - 2), если k > 2
						2, если k = 2

					Для остальных простых p наибольший порядок это значение функции Эйлера:
						phi(p^k) = p^k - p^(k - 1) = (p - 1) * p^(k - 1)
				*/

				int order = (p == 2) ?
					( (k == 2) ? 2 : power(p,k - 2) ):
					(p - 1) * power(p,k - 1);

				// Пользуюсь тем фактом, что НОК можно вычислять рекуррентно
				max_order = lcm(order,max_order);
			}
		}

		if(m > 1)
		{
			/*
				Для оставшейся части, это просто простой множитель:
					phi(p) = p - 1
			*/
			
			max_order = lcm(max_order,m - 1);
		}

		std::cout << max_order << std::endl;

	}

	return 0;
}