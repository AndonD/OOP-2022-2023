#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

#include "String.h"

String::String() : size(0), capacity(8), str(new char[capacity]) {}
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

void String::print() const
{
	std::cout << str << std::endl;
}