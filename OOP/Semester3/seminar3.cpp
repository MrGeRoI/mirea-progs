#include <iostream>

using namespace std;
class A
{
	void a()
	{
		cout << "non const\n";
	}

	void a() const
	{
		cout << "const\n";
	}
public:
	void b1()
	{
		a();
	}
	
	void b2() const
	{
		a();
	}
};

int main()
{
	A a;
	a.b1();
	a.b2();
	return 0;
}