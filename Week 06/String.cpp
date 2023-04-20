#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

// for example, we can include every other file in here as well, using this syntax
#include "Separated compilation/TestClass.h"

class String
{
private:
	char* str;
	size_t capacity;
	size_t size;

public:

	String()
	{
		this->size = 0;
		this->capacity = 8;
		this->str = new char[capacity];
		this->str[0] = '\0';
	}

	String(const char* content)
	{
		size = strlen(content);
		capacity = 8;
		while (capacity <= size)	//we include "=" because of the terminating null that is not counted by size
		{
			capacity *= 2;
		}

		str = new char[capacity];
		strcpy(str, content);
	}

	String(const String& other)
	{
		this->capacity = other.capacity;
		this->size = other.size;
		while (capacity <= size)
		{
			capacity *= 2;
		}
		this->str = new char[this->capacity];
		strcpy(this->str, other.c_str());
	}

	String& operator=(const String& other)
	{
		// check if the parameter of the function is the same, for example if we try to execute "str = str"
		if (this == &other)
		{
			return *this;
		}

		delete[] str;

		this->capacity = other.capacity;
		this->size = other.size;
		this->str = new char[this->capacity];
		strcpy(this->str, other.c_str());

		return *this;
	}

	~String()
	{
		delete[] str;
	}

	size_t length() const
	{
		return this->size;
	}

	char* c_str() const
	{
		return this->str;
	}

	void print() const
	{
		std::cout << str << std::endl;
	}
};

inline String concat(String first, String second)
{
	char* temp = new char[first.length() + second.length() + 1];
	strcpy(temp, first.c_str());
	strcat(temp, second.c_str());
	
	String result(temp);

	delete[] temp;
	return result;
}

int main()
{
	String str1("test ");
	String str2("another str");

	String str3 = concat(str1, str2);

	String str4 = str3 = String(str3);
	str3.print();
	str4.print();

	
	return 0;
}