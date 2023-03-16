#include <iostream>
#include <fstream>

const char* ERROR_MESSAGE = "Couldn't open file correctly\n";

//Task - shop

struct Product
{
	char* name;
	size_t quantity;
	float price;

	void print()
	{
		std::cout << name << std::endl;
		std::cout << quantity << std::endl;
		std::cout << price << std::endl;
	}
};


int main()
{
	// To open a file in binary mode, we need to use the std::ios::binary flag.
	// Everything is the same as when we open a normal file in stream
	std::fstream binary;
	binary.open("binary_files_demo.dat", std::ios::binary | std::ios::out | std::ios::in);
	if (!binary.is_open())
	{
		std::cerr << ERROR_MESSAGE;
		return -1;
	}

	char name[] = "apple";
	Product product{ name, 5, 2.45 };


	// Syntax for binary writing is:
	// fstreamName.write(<the object/variable to write into the file, casted to const char*>, <how many bytes we want to write into the file>)
	
	// Every type of information in the computer is represented with zeros (0) and ones (1).
	// It is the same when we try to use binary files - every object/variable we write is written in bytes.
	// For example, if we want to write an integer, 4 bytes will be written, and it will be the binary representation of the decimal integer.
	// Chars are represented by the binary form of their ASCII code.
	
	// NOTE that arrays and structures are fully written even if we do not use some of the allocated bytes.
	// For example if there is an array with 10 elements, but we only initialized 5 of them, 10 will be written.
	// In the case of writing a structure into binary file, we also write the bytes, used for the padding of the structure memory

	binary.write((const char*)&product, sizeof(Product));

	// We need to cast to char* because char is the type that is the nearest representation of a byte
	// We write only bytes when using binary files. And 'char' is the data type that is the nearest representation of a byte.
	// That's why we cast everything we want to write in binary file into char* - char because it is a byte, and pointer to it, because
	// this is the way to go through the following addresses of the memory block (the variable or object) we want to write

	Product product2;
	binary.seekg(0, std::ios::beg);

	// When using the read() member function, everything is the same as by write(), except that the first parameter type is char* and not const char*
	binary.read((char*)&product2, sizeof(Product));

	product2.print();

	binary.close();


	return 0;
}