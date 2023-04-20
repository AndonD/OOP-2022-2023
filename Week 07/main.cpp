#pragma warning(disable:4996)

#include <iostream>

#include "String.h"

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


	// When is move constructor or assignment operator used?

	// concat(str1, str2) returns a newly constructed String, not assigned or stored in a variable, so that means that it is
	// rvalue and therefore move assignment operator is called
	String str3 = concat(str1, str2);

	String str4 = str3 = String(str3);	// String(str3) is an rvalue, it means that move assignment operator is called

	// You can see that the move constructor and move operator= are executed by debugging

	str3.print();
	str4.print();

	return 0;
}