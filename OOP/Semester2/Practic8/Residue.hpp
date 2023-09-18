#include <vector>

template<typename N>
inline N mod(N a,N p)
{
	a = a % p;

    return a < 0 ? a + p : a;
}

template<typename N>
N power(N num,int degree)
{
	if(degree < 1)
		return 1;

	if(degree == 1)
		return num;

	N result = num;

	for(int i = 1;i < degree;i++)
		result *= num;

	return result;
}

template<typename N>
int get_multiplication_order(N n,N m)
{
	int order = 1;
	N r = n;

	while(r != 1)
	{
		if(r == 0)
			return -1;

		r = (r * n) % m;

		order++;
	}

	return order;
}

template<typename N>
N get_first_high_order_element(N prime,int degree)
{
	if(prime < 2 || degree < 1 || (prime == 2 && degree < 2))
		return 1;

	N modulo = power(prime,degree - 1);
	
	int high_order = (prime == 2) ?
		( (degree == 2) ? 2 : power(prime,degree - 2) ):
		(prime - 1) * modulo;

	modulo *= prime;

	for(N i = 2;i < modulo;i++)
	{
		if(get_multiplication_order(i,modulo) == high_order)
			return i;
	}

	return 0;
}

template<typename N>
N diophant(N a,N b)
{
	N u1 = b;
	N u2 = 0;
	N v1 = a;
	N v2 = 1;

	while (v1)
	{
		N q = u1 / v1;
		N t1 = u1 - q*v1;
		N t2 = u2 - q*v2;
		u1 = v1;
		u2 = v2;
		v1 = t1;
		v2 = t2;
	}

	return u2;
}

template<typename N>
std::vector<N> get_isomorphism(std::vector<N> modules)
{
	std::vector<N> elements(modules.size());

	for(int i = 0;i < modules.size();i++)
	{
		N a = 1;
		
		for(int j = 0;j < modules.size();j++)
			if(i != j)
				a *= modules[j];

		elements[i] = a * diophant(a,modules[i]);
	}

	return elements;
}

template<typename N>
N get_high_order_element(N modulo)
{
	N m = modulo;

	std::vector<N> primes;
	std::vector<N> degrees;

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

	N result = 0;

	for(int i = 0;i < primes.size();i++)
	{
		N high = get_first_high_order_element(primes[i],degrees[i]);

		std::vector<N> isomorphism = get_isomorphism(primes);

		N idempotent = high * isomorphism[i];

		result = result + idempotent;
	}

	return mod(result,modulo);
}
