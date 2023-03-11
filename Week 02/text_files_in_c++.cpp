#include <iostream>
#include <fstream>

const char* ERROR_MESSAGE = "File couldn't open correctly!\n";

int main()
{
	// how we used to read value to a variable and write from a variable until now - using the console
	int number;
	std::cin >> number;		// cin refers to console input
	std::cout << number;	// cout refers to console output
	// cin and cout come from <iostream> which stands for input/output stream

	
	const char* str = "Hello, world!\n";
	std::fstream ourFile;	// declaring a fstream (file stream) object
	ourFile.open("test.txt", std::ios::out | std::ios::trunc);	// opening a file stream
	// first parameter is the path + name of the file;
	// second parameter is the mode we want this stream to work on; we can combine more than one mode using the '|' character

	// BY DEFAULT when using ofstream if there is no file with the same name, the program will create it

	// second way of initializing a file stream
	std::fstream initByConstructor("test.txt", std::ios::out);

	// we should always check if the file is opened correctly
	if (!ourFile.is_open())
	{
		// cerr != cout
		// cerr (console error) is printing info on the console as cout does,
		// but doesn't use buffer (unlike cout) and is used to print error messages
		std::cerr << ERROR_MESSAGE;
	}
	
	ourFile << str;		// writing str into the file

	// we should always close a file stream when we no longer need it open
	ourFile.close();

	// we can open one stream again after it is closed; it can also be opened with another file path + name
	ourFile.open("example.txt", std::ios::out | std::ios::app);
	if (ourFile.is_open())
	{
		ourFile << "Second time opened this file!" << std::endl;
	}
	else
	{
		std::cerr << ERROR_MESSAGE;
	}
	ourFile.close();


	// exapmle for reading from file into a char array
	char input[100];
	ourFile.open("test.txt", std::ios::in | std::ios::out);

	if (ourFile.is_open())
	{
		while (!ourFile.eof())		// eof() is a function that returns true if the end of the file is reached, and false otherwise
		{
			int current = ourFile.tellg();	// tellg/tellp are methods that return the position which is reached in the stream for reading/writing
			ourFile.getline(input, 100);	// reading info from the stream to the input array

			ourFile.seekg(current + 15);	// seekg/seekp are methods used to change the position which is reached in the stream for reading/writing
			if (ourFile.good())		// note: please check these flags from the documentation - bad(), fail(), eof(), good()
			{
				std::cout << input << '\n';
			}
			else
			{
				break;
			}
		}
	}
	
	ourFile.close();

	return 0;
}