#include <iostream>
#include <fstream>

const char* ERROR_MESSAGE = "Couldn't open file correctly\n";

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
	std::fstream binary;

	// OPENING	!!!!!!!!!!!
	// Here there was a problem when we tried opening it by using:
	// 'binary.open("binary_files_demo.dat", std::ios::binary | std::ios::in'| std::ios::out)'
	// The program would work only when there is such a file before running the program. It wasn't possible to create and open it
	// if it haven't existed.
	// 
	// Turns out that it would work if we use ALSO the std::ios::app flag when trying to open it.
	// There are many combinations of those possible flags and modes for opening a file. And there is
	// a strictly known expected result for each of the combinations and it is written in this link:
	// 
	// https://en.cppreference.com/w/cpp/io/basic_filebuf/open
	// 
	// Also note that in every try to open a file, the opening mode is determined by
	// (<a flag we write> | <a flag we write> | <and more flags we want etc.>) & std::ios::ate
	//

	// After reading the info above, we know that this line will create the file if it doesn't exist
	binary.open("binary_files_demo.dat", std::ios::binary | std::ios::in | std::ios::app);
	if (!binary.is_open())
	{
		std::cerr << ERROR_MESSAGE;
		return -1;
	}

	char name[10] = "apple";
	Product product{ name, 5, 2.45 };
	char name2[10] = "apple";
	Product product2{name2, 3, 1};
	char name3[10] = "apple";
	Product product3{ name3, 7, 1 };

	std::cout << std::boolalpha << binary.eof() << std::endl;	// check again for any case the we are not in the end of the file

	binary.write((const char*)&product, sizeof(Product));
	binary.write((const char*)&product2, sizeof(Product));
	binary.write((const char*)&product3, sizeof(Product));


	// Here we demonstrate one of the main advantages of binary files!
	// It is that, when we know exactly how many bytes does an object use for its representation in the file, we can
	// go through the file to the exact streampos where a specific object is represented/written.
	// That wouldn't be possible with the text files, because in that case we wouldn't know how many ASCII characters does the object use
	// to be written

	Product productToTest;	// the object in which we will save the info from the file to test if it is the exact object in file we want

	// We skip the first 2 Products in the file (because of 2*sizeof(Product)) by setting the streampos to the beginning of the third one
	binary.seekg(2*sizeof(Product), std::ios::beg);

	binary.read((char*)&productToTest, sizeof(Product));	// Here the product we want is read and saved into 'productToTest'

	productToTest.print();

	binary.close();

	return 0;
}