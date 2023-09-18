#include <iostream>

/*	Иерарихия:

	   A1

	B1 B2 B3
	
	  C1 C2

		D1
*/

class A1
{
protected:
	int _a;

public:
	A1()
	{
		_a = 0;
	}

	A1(int a)
	{
		_a = a;
	}

	virtual void Print()
	{
		std::cout << "A1" << std::endl;
	}

	virtual void Show()
	{
		std::cout << "\ta = " << _a << std::endl;
	}
};

class B1 : virtual public A1
{
protected:
	int _b;

public:
	B1() : A1(0)
	{
		_b = 0;
	}

	B1(int a,int b) : A1(a)
	{
		_b = b;
	}

	virtual void Print() override
	{
		std::cout << "B1" << std::endl;
	}

	virtual void Show() override
	{
		std::cout << "\ta = " << _a << std::endl <<
			"\tb = " << _b << std::endl;
	}
};

class B2 : virtual public A1
{
protected:
	int _b;

public:
	B2() : A1(0)
	{
		_b = 0;
	}

	B2(int a,int b) : A1(a)
	{
		_b = b;
	}

	virtual void Print() override
	{
		std::cout << "B2" << std::endl;
	}

	virtual void Show() override
	{
		std::cout << "\ta = " << _a << std::endl <<
			"\tb = " << _b << std::endl;
	}
};

class B3 : virtual public A1
{
protected:
	int _b;

public:
	B3() : A1(0)
	{
		_b = 0;
	}

	B3(int a,int b) : A1(a)
	{
		_b = b;
	}

	virtual void Print() override
	{
		std::cout << "B3" << std::endl;
	}

	virtual void Show() override
	{
		std::cout << "\ta = " << _a << std::endl <<
			"\tb = " << _b << std::endl;
	}
};

class C1 : virtual public B1 , virtual public B2 , virtual public B3
{
protected:
	int _c;

public:
	C1(int a1,int a2,int a3,
		int b1,int b2,int b3,
		int c) : B1(a1,b1) , B2(a2,b2) , B3(a3,b3)
	{
		_c = c;
	}

	virtual void Print() override
	{
		std::cout << "C1" << std::endl;
	}

	virtual void Show() override
	{
		std::cout << "\ta = " << _a << std::endl <<
			"\tb (B1) = " << B1::_b << std::endl <<
			"\tb (B2) = " << B2::_b << std::endl <<
			"\tb (B3) = " << B3::_b << std::endl <<
			"\tc = " << _c << std::endl;
	}
};

class C2 : virtual public B1 , virtual public B2 , virtual public B3
{
protected:
	int _c;

public:
	C2(int a1,int a2,int a3,
		int b1,int b2,int b3,
		int c) : B1(a1,b1) , B2(a2,b2) , B3(a3,b3)
	{
		_c = c;
	}

	virtual void Print() override
	{
		std::cout << "C2" << std::endl;
	}

	virtual void Show() override
	{
		std::cout << "\ta = " << _a << std::endl <<
			"\tb (B1) = " << B1::_b << std::endl <<
			"\tb (B2) = " << B2::_b << std::endl <<
			"\tb (B3) = " << B3::_b << std::endl <<
			"\tc = " << _c << std::endl;
	}
};

class D1 : virtual public C1 , virtual public C2
{
protected:
	int _d;

public:
	D1(int a1,int a2,int a3,int a4,int a5,int a6,
		int b1,int b2,int b3,int b4,int b5,int b6,
		int c1,int c2,int d) : C1(a1,a2,a3,b1,b2,b3,c1) , C2(a4,a5,a6,b4,b5,b6,c2)
	{
		_d = d;
	}

	virtual void Print() override
	{
		std::cout << "D1" << std::endl;
	}

	virtual void Show() override
	{
		std::cout << "\ta = " << _a << std::endl <<
			"\tb (B1) = " << B1::_b << std::endl <<
			"\tb (B2) = " << B2::_b << std::endl <<
			"\tb (B3) = " << B3::_b << std::endl <<
			"\tc (C1) = " << C1::_c << std::endl <<
			"\tc (C2) = " << C2::_c << std::endl <<
			"\td = " << _d << std::endl;
	}
};

int main()
{
	A1 a1(1);

	a1.Print();
	a1.Show();

	B3 b3(2,3);

	b3.Print();
	b3.Show();

	C2 c2(4,5,6,7,8,9,10);

	/*
		Здесь в поле класса А,
		если передавать в конструктор класса А разные значения через конструкторы производных классов,
		будет значение из стандартного конструктора класса A, т.е. 0 в моём случае
	*/
	c2.Print();
	c2.Show();

	D1 d1(11,12,13,14,15,16,17,18,19,20,21,22,23,24,25);

	d1.Print();
	d1.Show();

	/*
		Выводит всю информацию о объекте pa1 как о классе D1, несмотря на то,
		что рассматривается как указатель на класс A1, благодаря виртуальным функциям
	*/
	A1* pa1 = &d1;
	pa1->Print();
	pa1->Show();

	return 0;
}