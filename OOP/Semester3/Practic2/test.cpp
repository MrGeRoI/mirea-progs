#include <map>
#include <iostream>

using namespace std;

int main()
{
	map<int, int> nums;

	nums[4] = 4;
	nums[3] = 3;
	nums[5] = 5;
	nums[6] = 6;

	for(typename map<int,int>::iterator it = nums.begin();it != nums.end();it++)
		cout << it->second << " ";

}
