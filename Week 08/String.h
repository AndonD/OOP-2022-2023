#pragma once

#include <iostream>

class String
{
private:
	char* str;
	size_t capacity;
	size_t size;

public:

	// constructors and assignment operators
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

	//operators
	bool operator==(const String&) const;
	bool operator!=(const String&) const;
	bool operator<(const String&) const;
	bool operator>(const String&) const;
	String operator+(const String&) const;
	String& operator+=(const String&);

	void print() const;
};