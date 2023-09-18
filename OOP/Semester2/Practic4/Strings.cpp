#include <iostream>

#define STRING_MIN_LENGTH 256

class BaseString
{
protected:
	int _length,_capacity;

	char* _ptr;
public:
	// конструктор по размеру
	BaseString(int capacity = STRING_MIN_LENGTH)
	{
		_capacity = capacity > STRING_MIN_LENGTH ? capacity : STRING_MIN_LENGTH;
		_length = 0;
		_ptr = new char[_capacity]{'\0'};
	};

	// конструктор из нуль-терминированной строки
	BaseString(char* pstr)
	{
		_length = 0;
		while(pstr[_length] != '\0')
			_length++;

		_capacity = _length + 1 > STRING_MIN_LENGTH ? _length + 1 : STRING_MIN_LENGTH;

		_ptr = new char[_capacity];

		for(int i = 0;i <= _capacity;i++)
			_ptr[i] = pstr[i];
	};

	BaseString(const char* cstr)
	{
		_length = 0;
		while(cstr[_length] != '\0')
			_length++;

		_capacity = _length + 1 > STRING_MIN_LENGTH ? _length + 1 : STRING_MIN_LENGTH;

		_ptr = new char[_capacity];

		for(int i = 0;i <= _capacity;i++)
			_ptr[i] = cstr[i];
	};

	// конструктор копии
	BaseString(const BaseString& str)
	{
		_capacity = str._capacity;
		_length = str._length;

		_ptr = new char[str._capacity];
		
		for(int i = 0;i <= str._length;i++)
			_ptr[i] = str._ptr[i];
	};

	// деструктор
	~BaseString()
	{
		if(_ptr != nullptr)
			delete[] _ptr;

		_length = 0;
	};

	int GetLength()
	{
		return _length;
	};

	int GetCapacity()
	{
		return _capacity;
	};

	char GetChar(int index)
	{
		if(index < 0 || index >= _length)
			return '\0';

		return _ptr[index];
	};

	int IndexOf(char c,int index = -1)
	{
		if(index == -1)
			index = 0;
			
		/*
		for(char* p = _ptr;*p != '\0';p++)
			if(*p == c)
				return p - _ptr;
		*/

		for(int i = index;i < _length;i++)
			if(_ptr[i] == c)
				return i;

		return -1;
	}

	bool IsPalindrome()
	{
		if(_length < 2)
			return true;
			
		char* p1 = _ptr;
		char* p2 = &_ptr[_length - 1];

		while(p1 < p2)
		{
			if(*p1 != *p2)
				return false;

			p1++;
			p2--;
		}

		return true;
	}

	// получить нуль-терминированную строку
	char* GetPointer()
	{
		return _ptr;
	};

	BaseString& operator =(BaseString str)
	{
		if(_capacity != str._capacity)
		{
			delete[] _ptr;
			_ptr = new char[str._capacity];
			_capacity = str._capacity;
		}

		_length = str._length;

		for(int i = 0;i < str._capacity;i++)
			_ptr[i] = str._ptr[i];
		
		return *this;
	};

	friend std::ostream& operator <<(std::ostream& stream,BaseString& str);
};

std::ostream& operator <<(std::ostream& stream,BaseString& str)
{
	stream << str._ptr;
	return stream;
}

class ChildString : public BaseString
{
protected:

public:
    ChildString(int capacity = STRING_MIN_LENGTH) : BaseString(capacity) { };

	ChildString(char* pstr) : BaseString(pstr) { };

	ChildString(const char* cstr) : BaseString(cstr) { };

    ChildString(const ChildString& str) : BaseString(str) { };

	int IndexOfLast(char c,int index = -1)
	{
        if(index == -1)
            index = _length - 1;

		for(int i = index;i >= 0;i--)
			if(_ptr[i] == c)
				return i;

		return -1;
	}

	void Append(char c,bool bInStart = false)
	{
		if(_length >= _capacity - 1);
			return;
		
		if(bInStart)
			;
		else
		{
			_ptr[_length] = c;
			_ptr[_length + 1] = '\0';
			_length++;
		}
	}

    ChildString Trim()
    {
        int start = _length,end = 0;

        for(int i = 0;i < _length;i++)
            if(_ptr[i] != ' ')
            {
                start = i;
                break;
            }

        for(int i = _length - 1;i >= 0;i--)
            if(_ptr[i] != ' ')
            {
                end = i;
                break;
            }

        if(start > end)
            return ChildString();

        int len = end - start + 1;

		ChildString trimmed(len + 1);

        for(int i = 0;i < len;i++)
            trimmed._ptr[i] = _ptr[i + start];

        trimmed._ptr[len + 1] = '\0';
        trimmed._length = len;

        return trimmed;
    };

    ~ChildString() { };

};

int main()
{
	ChildString str1("  5 AB ");
	std::cout << "str1:\t\t\"" << str1 << '\"'  << std::endl; // Выводит: "  5 AB "

	ChildString trimmed1 = str1.Trim();
	std::cout << "trimmed1:\t\"" << trimmed1 << '\"' << std::endl; // Выводит: "5 AB"

	return 0;
}