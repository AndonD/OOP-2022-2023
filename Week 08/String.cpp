#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

#include "String.h"

String::String()
{
	this->size = 0;
	this->capacity = 8;
	this->str = new char[capacity];
	this->str[0] = '\0';
}

String::String(const char* content)
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

String::String(const String& other)
{
	this->capacity = other.capacity;
	this->size = other.size;

	this->str = new char[this->capacity];
	strcpy(this->str, other.c_str());
}


// Move constructor
// && means a rvalue reference
String::String(String&& other)
{
	this->capacity = other.capacity;
	this->size = other.size;

	this->str = other.str;

	other.str = nullptr;
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		delete[] str;

		this->capacity = other.capacity;
		this->size = other.size;
		this->str = new char[this->capacity];
		strcpy(this->str, other.c_str());
	}

	return *this;
}

// Move operator =
String& String::operator=(String&& other)
{
	if (this != &other)
	{
		delete[] str;

		this->capacity = other.capacity;
		this->size = other.size;
		this->str = other.str;

		other.str = nullptr;
	}

	return *this;
}

String::~String()
{
	delete[] str;
}

size_t String::length() const
{
	return this->size;
}

char* String::c_str() const
{
	return this->str;
}

bool String::operator==(const String& other) const
{
	return !strcmp(this->str, other.str);
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

bool String::operator<(const String& other) const
{
	return strcmp(this->str, other.str) < 0;
}

bool String::operator>(const String& other) const
{
	//return !(*this < other);	// includes case when they are equal
	return strcmp(this->str, other.str) > 0;
}

String String::operator+(const String& other) const
{
	String result;
	result += *this;
	result += other;
	return result;
}

String& String::operator+=(const String& other)
{
	char* temp = new char[this->size + other.length() + 1];
	strcpy(temp, this->str);
	strcat(temp, other.str);

	*this = String(temp);
	delete[] temp;

	return *this;
}

String& String::operator+=(const char& c)
{
	char* temp = new char[this->size + 1 + 1];	// +1 for the char and +1 for the terminating null
	strcpy(temp, this->str);
	temp[this->size] = c;
	temp[this->size + 1] = '\0';

	*this = String(temp);
	delete[] temp;

	return *this;
}

void String::print() const
{
	std::cout << str << std::endl;
}

// friend operators

std::ostream& operator<< (std::ostream& out, const String& str)
{
	out << str.c_str();
	return out;
}

std::istream& operator>> (std::istream& in, String& str)
{
	char c;
	while ((c = in.get()) != '\n')
	{
		str += c;
	}

	return in;
}