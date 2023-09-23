#include <list>
#include <iostream>

using namespace std;

class B
{
public:
	int num;
};

class A
{
private:
	int num;
	B *b;
public:
	A() : num(228) { b = new B(); b->num = 10; }

	int& operator * () { return b->num;}
	const int& operator * () const { return b->num;}

	~A() { delete b; }
};

int main()
{
	A a;
	*a = 123;
	cout << *a << endl;


	return 0;
}
