#include <iostream>
#include <fstream>

int main()
{
	//	Напишете програма, която отпечатва на екрана собствения си код.

	std::fstream program("Week2.cpp", std::ios::in);

	if (!program.is_open())
	{
		std::cerr << "File couldn't open correctly\n";
		return -1;
	}

	char line[100];
	while (!program.eof())
	{
		program.getline(line, 100, '\n');
		
		// Note that there are lines, longer than 100 elements. The ifstream.getline() member function will in this case turn on the fail-flag
		// if it haven't found the '\n' symbol in those 100 chars.
		// If we do not clear the flags after that, we will not be able to use the stream (program in this case)
		// That's why we check it and clear it if there is such a situation and getline continues from the next character on the next iteration
		if (program.fail())
		{
			program.clear();
		}
		std::cout << line << '\n';
	}

	program.close();

	return 0;
}