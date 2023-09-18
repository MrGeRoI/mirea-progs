#pragma once

#include <iostream>
#include <string>

/*«Школьник».
Минимальный набор полей: фамилия,
имя, пол, класс, дата рождения, адрес.*/
class Student
{
public:
	std::string _firstname, _lastname, _address;
	bool _male;
	int _birthday,_grade;

	Student()
	{
		_male = 0;
		_birthday = 0;
		_grade = 0;
	}

	Student(const char* firstname,const char* lastname,const char* address,bool male, int birthday,int grade)
	{
		_firstname = firstname;
		_lastname = lastname;
		_address = address;
		_male = male;
		_birthday = birthday;
		_grade = grade;
	}

	Student(const Student& stud)
	{
		_firstname = stud._firstname;
		_lastname = stud._lastname;
		_address = stud._address;
		_male = stud._male;
		_birthday = stud._birthday;
		_grade = stud._grade;
	}

	~Student() { }

	friend std::ostream& operator << (std::ostream& s,const Student& value);
	friend std::istream& operator >> (std::istream& s, Student& value);

	bool operator < (const Student& stud) const
	{
		if(_birthday < stud._birthday)
			return true;

		if(_lastname < stud._lastname)
			return true;

		if(_firstname < stud._firstname)
			return true;

		return false;
	}

	bool operator > (const Student& stud) const
	{
		if(_birthday > stud._birthday)
			return true;

		if(_lastname > stud._lastname)
			return true;

		if(_firstname > stud._firstname)
			return true;

		return false;
	}

	bool operator == (const Student& stud) const
	{
		return _firstname == stud._firstname &&
			_lastname == stud._lastname &&
			_birthday == stud._birthday;
	}
};

std::ostream& operator << (std::ostream& stream,const Student& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

std::istream& operator >> (std::istream& stream, Student& value)
{
	return stream >> value._firstname >> value._lastname >> value._address >> value._male >> value._birthday >> value._grade;
}
