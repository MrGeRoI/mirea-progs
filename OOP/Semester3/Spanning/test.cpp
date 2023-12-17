class A
{
protected:
	int bar;
};

class B : public A
{
public:
	int foo(A& a)
	{
		a.bar = 1;
	}
};