#include <stdio.h>
#include <math.h>

long long powi(long long a,int b)
{
	long long r = 1;

	for(int i = 0;i < b;i++)
		r *= a;

	return r;
}

int main(int argc, char* argv[])
{
	long long m = 6;
	long long a = 5;

	printf("Enter a: ");
	scanf("%lld",&a);

	for(int i = 1;i < 10;i++)
	{
		printf("%lld^%d = %lld(mod %lld)\n",a,i,powi(a,i) % m,m);
	}

	return 0;
}
