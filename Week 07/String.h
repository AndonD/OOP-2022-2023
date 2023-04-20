#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

class String
{
private:
	char* str;
	size_t capacity;
	size_t size;

public:

	//constructors
	String();
	String(const char*);
	String(const String&);
	String(String&&);
	String& operator=(const String&);
	String& operator=(String&&);
	~String();

	//getters
	size_t length() const;
	char* c_str() const;

	void print() const;
};