#include <vector>
#include <iostream>

using namespace std;

void jopa(vector<int>& vec1,vector<int>& vec2)
{
	vec1.push_back(3);
	vec1.push_back(5);

	vec2.push_back(7);
}

int main()
{
	vector<int> vec1,vec2;

	jopa(vec1,vec2);

	for(int x : vec1)
		cout << x << endl;

	for(int x : vec2)
		cout << x << endl;

	return 0;
}
