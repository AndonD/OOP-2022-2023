#pragma warning(disable:4996)

#include <iostream>
#include <cstring>
#include <fstream>

const char* ERROR_MESSAGE = "Couldn't open file correctly\n";

struct Product_With_Static_Array
{
	char name[10];
	size_t quantity;
	float price;

	void print()
	{
		std::cout << name << std::endl;
		std::cout << quantity << std::endl;
		std::cout << price << std::endl;
	}
};

struct Product_With_Dynamic_Array
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

	char name[10] = "apple 1";
	Product_With_Static_Array product;
	strcpy(product.name, name);
	product.quantity = 5;
	product.price = 2.45;

	char name2[10] = "apple 2";
	Product_With_Static_Array product2;
	strcpy(product2.name, name2);
	product2.quantity = 3;
	product2.price = 1;

	char name3[10] = "apple 3";
	Product_With_Static_Array product3;
	strcpy(product3.name, name3);
	product3.quantity = 7;
	product3.price = 1;


	std::cout << std::boolalpha << binary.eof() << std::endl;	// check again for any case the we are not in the end of the file

	binary.write((const char*)&product, sizeof(Product_With_Static_Array));
	binary.write((const char*)&product2, sizeof(Product_With_Static_Array));
	binary.write((const char*)&product3, sizeof(Product_With_Static_Array));

	// We should always check if the input/output operations (or series of such operations) are successfully executed
	// This is done for example by checking the fstream state
	if (!binary)
	{
		std::cerr << "Something went wrong when writing to the file\n";
		// here we can close the file, or clear it or do some other kind of error handling
	}


	// Here we demonstrate one of the main advantages of binary files!
	// It is that, when we know exactly how many bytes does an object use for its representation in the file, we can
	// go through the file to the exact streampos where a specific object is represented/written.
	// That wouldn't be possible with the text files, because in that case we wouldn't know how many ASCII characters does the object use
	// to be written

	Product_With_Static_Array productToTest;	// the object in which we will save the info from the file to test if it is the exact object in file we want

	// We skip the first 2 Products in the file (because of 2*sizeof(Product_With_Static_Array)) by setting the streampos to the beginning of the third one
	binary.seekg(2 * sizeof(Product_With_Static_Array), std::ios::beg);
	binary.read((char*)&productToTest, sizeof(Product_With_Static_Array));	// Here the product we want is read and saved into 'productToTest'
	if (!binary)
	{
		std::cerr << "Something went wrong when writing to the file\n";
		// file stream error handling
	}

	productToTest.print();
	binary.close();

	
	// DYNAMIC ARRAYS

	binary.open("binary_files_dynamic.dat", std::ios::binary | std::ios::in | std::ios::app);
	if (!binary.is_open())
	{
		std::cerr << ERROR_MESSAGE;
		return -1;
	}

	Product_With_Dynamic_Array dynamic;
	char str[] = "cherry";	// the type can also be "const char*" and it will be the same to use
	dynamic.name = new char[strlen(str) + 1];
	strcpy(dynamic.name, str);
	dynamic.quantity = 20;
	dynamic.price = 2.20;

	// Writing the product "dynamic" to a binary file
	// Pay attention to how we write the str data member
	size_t nameLength = strlen(dynamic.name);					// or strlen(dynamic.name) + 1 if you want to write also the terminating null
	binary.write((const char*)&nameLength, sizeof(nameLength));	// or sizeof(nameLength + 1) for terminating null
	binary.write(dynamic.name, nameLength);	// note why we do not cast "dynamic.name" and why we don't use sizeof()
	binary.write((const char*)&dynamic.quantity, sizeof(dynamic.quantity));
	binary.write((const char*)&dynamic.price, sizeof(dynamic.price));
	if (!binary)
	{
		std::cerr << "Something went wrong when writing to the file\n";
		// file stream error handling
	}

	delete[] dynamic.name;	// free the memory used by "dynamic"

	// Reading
	Product_With_Dynamic_Array toRead;
	binary.read((char*)&nameLength, sizeof(nameLength));
	toRead.name = new char[nameLength + 1];	// if we write the terminating null in the file, here would be nameLength (without +1)
	binary.read(toRead.name, nameLength);
	toRead.name[nameLength] = '\0';

	binary.read((char*)&toRead.quantity, sizeof(toRead.quantity));
	binary.read((char*)&toRead.price, sizeof(toRead.price));
	if (!binary)
	{
		std::cerr << "Something went wrong when writing to the file\n";
		// file stream error handling
	}

	toRead.print();
	delete[] toRead.name;	// free the memory used by "toRead"

	binary.close();

	return 0;
}