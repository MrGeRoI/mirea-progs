#include <iostream>
#include <vector>

// Вся арифметика в long long'ах
using number = long long;

// Взятие по модулю (с учётом знака!!!)
inline number mod(number a,number p)
{
	a = a % p;

    return a < 0 ? a + p : a;
}

number power(number num,int degree)
{
	if(degree < 1)
		return 1;

	if(degree == 1)
		return num;

	number result = num;

	for(int i = 1;i < degree;i++)
		result *= num;

	return result;
}

int get_multiplication_order(const number n,const number m)
{
	int order = 1;
	number r = n;

	while(r != 1)
	{
		if(r == 0)
			return -1;

		r = (r * n) % m;

		order++;
	}

	return order;
}

number get_first_high_order_element(const number prime,const int degree)
{
	// Инвариант: prime - простое

	if(prime < 2 || degree < 1 || (prime == 2 && degree < 2))
		return 1;

	number modulo = power(prime,degree - 1);
	
	/*
		Для p = 2 наибольший порядок это:
			2^(n - 2)

		Для остальных простых p наибольший порядок это значение функции Эйлера:
			phi(p^n) = p^n - p^(n - 1) = (p - 1) * p^(n - 1)
	*/

	int high_order = (prime == 2) ?
		( (degree == 2) ? 2 : power(prime,degree - 2) ):
		(prime - 1) * modulo;

	modulo *= prime;

	for(int i = 2;i < modulo;i++)
	{
		if(get_multiplication_order(i,modulo) == high_order)
			return i;
	}

	return 0;
}

// Нахождение обратного числа по модулю p по алгоритму Евклида
number diophant(number a,number b)
{
	// Инвариант: p - простое <=> всегда есть обратный к a
	number u1 = b;
	number u2 = 0;
	number v1 = a;
	number v2 = 1;
	/* Хазиевские таблицы
		[	a	p	]
		[	u1	v1	]
		[	u2	v2	]
	*/
	while (v1)
	{
		number q = u1 / v1;
		number t1 = u1 - q*v1;
		number t2 = u2 - q*v2;
		u1 = v1;
		u2 = v2;
		v1 = t1;
		v2 = t2;
	}

	return u2;
}

std::vector<number> get_isomorphism(std::vector<number> modules)
{
	std::vector<number> elements(modules.size());

	for(int i = 0;i < modules.size();i++)
	{
		number a = 1;
		
		for(int j = 0;j < modules.size();j++)
			if(i != j)
				a *= modules[j];

		elements[i] = a * diophant(a,modules[i]);
	}

	return elements;
}

int main(int argc,char* argv[])
{
	std::vector<number> test = {
		61,
		800,
		55450,
		2383254,
		316030564,
		730887505,
		1847653789,
		1478783811,
	};

	for(number n : test)
	{
		number m = n;

		std::vector<number> primes;
		std::vector<number> degrees;

		for(int i = 2;i*i < m;i++)
		{
			int degree = 0;

			while(m % i == 0)
			{
				m /= i;
				degree++;
			}

			if(degree > 1)
			{
				primes.push_back(i);
				degrees.push_back(degree);
			}
		}

		if(m > 1)
		{
			primes.push_back(m);
			degrees.push_back(1);
		}

		number result = 0;

		for(int i = 0;i < primes.size();i++)
		{
			number high = get_first_high_order_element(primes[i],degrees[i]);

			std::vector<number> isomorphism = get_isomorphism(primes);

			number idempotent = high * isomorphism[i];

			result = result + idempotent;
		}

		std::cout << "Result: " << mod(result,n) << " in " << n << std::endl;
	}

	return 0;
}