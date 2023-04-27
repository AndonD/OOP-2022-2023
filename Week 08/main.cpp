#include <iostream>
#include <cstring>

#include "String.h"

int main()
{
	String str("apple");
	String str2(" txt");
	String str3(" sdnk");

	str += str2 += str3;
	std::cout << str;
}