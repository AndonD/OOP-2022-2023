#include <iostream>

#include "String.h"

int main()
{
	/*String str("text 1");
	String str2(" text 2");

	std::cout << str << str2 << std::endl;*/

	String s;
	std::cin >> s;
	//std::cout << s;

	std::cout << s[3] << std::endl;
	s[3] = 't';
	std::cout << s << std::endl;

	return 0;
}

