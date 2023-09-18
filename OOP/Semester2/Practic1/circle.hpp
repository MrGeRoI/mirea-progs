#pragma once

#include <algorithm>

//Вариант 19
//Окружность (радиус и 2 координаты)
class Circle
{
private:
	double _radius, _x, _y;
public:
	//конструкторы
	Circle(double x, double y,double r)
	{
		_x = x;
		_y = y;
		_radius = std::max(r, 0.0);
	}

	Circle(double x, double y)
	{
		_x = x;
		_y = y;
		_radius = 1.0;
	}

	Circle(double r)
	{
		_x = 0.0;
		_y = 0.0;
		_radius = std::max(r,0.0);
	}

	Circle()
	{
		_x = 0.0;
		_y = 0.0;
		_radius = 0.0;
	}

	//геттеры
	double GetX() { return _x; }
	double GetY() { return _y; }
	double GetRadius() { return _radius; }

	//сеттеры
	void SetX(double x) { _x = x; }
	void SetY(double y) { _y = y; }
	void SetRadius(double r) { _radius = std::max(r,0.0); }

	//Операция сравнения < (сравнение по радиусу), унарная операция – находится ли окружность полностью в одной из четвертей (bool)
	bool operator <(Circle c)
	{
		return _radius < c._radius;
	}

	//Унарная операция – находится ли окружность полностью в одной из четвертей (bool)
	bool operator +()
	{
		return abs(_x) >= _radius && abs(_y) > _radius;
	}

	//Унарная операция – в какой четверти полностью находится окружность. Если однозначного ответа нет, вернуть 0 (int)
	int operator -()
	{
		if (_x >= _radius)
		{
			if (_y >= _radius)
				return 1;
			else if (_y <= -_radius)
				return 4;
		}
		else if (_x <= -_radius)
		{
			if (_y >= _radius)
				return 2;
			else if (_y <= -_radius)
				return 3;
		}

		return 0;
	}
};