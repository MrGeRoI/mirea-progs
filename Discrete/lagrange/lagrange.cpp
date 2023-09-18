#include <iostream>
#include <fstream>
#include <vector>

// Вся арифметика в long long'ах
using number = long long;

// Взятие по модулю (с учётом знака!!!)
inline number mod(number a,number p)
{
	a = a % p;

    return a < 0 ? a + p : a;
}

// Нахождение обратного числа по модулю p по алгоритму Евклида
number inverse(number a,number p)
{
	// Инвариант: p - простое <=> всегда есть обратный к a
	number u1 = p;
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

	return mod(u2,p);
}

int main(int argc,char* argv[])
{
	for(int f = 1;f <= 8;f++)
	{
		number p,x;
		int n;

		std::ifstream file(std::string("test") + std::to_string(f) + std::string(".in"));

		file >> p >> x >> n;

		std::vector<int> xs(n),ys(n);

		for(int i = 0;i < n;i++)
			file >> xs[i] >> ys[i];

		file.close();
		
		number result = 0;

		for(int i = 0;i < n;i++)
		{
			if(ys[i] == 0)
				continue;

			number num = ys[i],denom = 1;

			for(int j = 0;j < n;j++)
			{
				if(j == i)
					continue;

				num = mod(num * (x - xs[j]),p);
				denom = mod(denom * (xs[i] - xs[j]),p);
			}
			
			number poly = mod(num * inverse(denom,p),p);
			result = mod(result + poly,p);
		}

		std::cout << "test" << f << ".in: " << result << std::endl;
	}
	
	return 0;
};