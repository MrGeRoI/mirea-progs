#include <iostream>

int order(const int x,const int m)
{
	int n = x;
	int k = 2;

	//std::cout << x << "^1 ≡ " << x << " (mod " << m << ')' << std::endl;

	for(;n != 1;k++)
	{
		n = (n * x) % m;
		
		if(n == x)
			return -1;

		//std::cout << x << '^' << k << " ≡ " << n << " (mod " << m << ')' << std::endl;
	}
	
	//std::cout << "Order(" << x << ',' << m << ") = " << k - 1 << std::endl;

	return k - 1;
}

int main(int argc,char* argv[])
{
	//order(8,11);

	for(int n = 2;n < 385;n++)
	{
		std::cout << "Order(" << n << ',' << 385 << ") = " << order(n,385) << std::endl;
	}

	return 0;
}