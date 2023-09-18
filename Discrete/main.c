#include <stdio.h>
#include <math.h>

int is_valid(int x)
{
	int sevens = 0;
	while(x > 0)
	{
		if(x % 10 == 0)
			return 0;

		if(x % 10 == 7)
			sevens++;

		x = x / 10;
	}
	return sevens >= 2;
}

int main(int argc, char* argv[])
{
	int count = 0;

    for(int i = 11111;i < 100000;i++)
		if(is_valid(i))
			count++;

	printf("count: %d\n",count);
	return 0;
}
