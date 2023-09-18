#include <iostream>
#include <vector>

int main(int argc,char* argv[])
{
	for(int i : std::vector{5,7,9})
	{
		for(int j = 2;j < i;j++)
		{
			if(j*j % (i) == j)
			{
				std::cout << "Idem: " << j << " in " << i << std::endl;
			}
		}
	}

	return 0;
}