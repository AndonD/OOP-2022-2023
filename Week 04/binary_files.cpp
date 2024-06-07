#pragma warning(disable:4996)	// disabling warnings about using strcpy instead of strcpy_s
#include <iostream>
#include <cstring>
#include <fstream>

const char* ERROR_MESSAGE = "Couldn't open file correctly\n";

struct Product_With_Static_Array
{
	char name[10];
	size_t quantity;
	float price;

	void print() const
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

	void print() const
	{
		std::cout << name << std::endl;
		std::cout << quantity << std::endl;
		std::cout << price << std::endl;
	}
};

struct Product_With_String
{
	std::string name;
	std::string note;
	size_t quantity;
	float price;

	void print() const
	{
		std::cout << name << std::endl;
		std::cout << quantity << std::endl;
		std::cout << price << std::endl;
	}
};


int main()
{
	std::fstream binary;

	// See here more info on opening files with different flags: https://en.cppreference.com/w/cpp/io/basic_filebuf/open
	 
	binary.open("binary_files_demo.dat", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
	if (!binary)
	{
		std::cerr << ERROR_MESSAGE;
		return -1;
	}

	char name[10] = "apple 1";
	Product_With_Static_Array product;
	strcpy(product.name, name);
	product.quantity = 5;
	product.price = 2.45f;

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

	// seekg and tellg are used to set where in the file we want to start read/write
	// Read more in the following links:
	// https://www.geeksforgeeks.org/read-a-record-from-a-file-in-c-using-seekg-and-tellg/
	// https://cplusplus.com/reference/istream/istream/tellg/
	// https://cplusplus.com/reference/istream/istream/seekg/
	
	
	// In order to read the 3rd Product we skip the first 2 Products in the file (because of 2*sizeof(Product_With_Static_Array)) by setting the streampos to the beginning of the third one
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

	binary.open("binary_files_dynamic.dat", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
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
	dynamic.price = 2.20f;

	// Writing the product "dynamic" to a binary file
	// Pay attention to how we write the str data member
	size_t nameLength = strlen(dynamic.name);					// or strlen(dynamic.name) + 1 if you want to write also the terminating null
	binary.write((const char*)&nameLength, sizeof(nameLength));
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
	binary.seekg(0, std::ios::beg);	// returning the pointer in the file to the beginning

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


	// STRINGS

	binary.open("binary_files_strings.dat", std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
	if (!binary.is_open())
	{
		std::cerr << ERROR_MESSAGE;
		return -1;
	}

	Product_With_String strProd;
	strProd.name = "cherry string";
	strProd.quantity = 100;
	strProd.price = 5.20f;

	// Writing the product "strProd" to a binary file
	
	nameLength = strProd.name.size();					// or strProd.size() + 1 if you want to write also the terminating null
	binary.write((const char*)&nameLength, sizeof(nameLength));
	binary.write(strProd.name.c_str(), nameLength);	// note why we do not cast "strProd.name.c_str()" and why we don't use nameLength * sizeof()

	size_t noteLength = strProd.note.size();
	binary.write((const char*)&noteLength, sizeof(noteLength));
	binary.write(strProd.note.c_str(), noteLength);
	
	binary.write((const char*)&strProd.quantity, sizeof(strProd.quantity));
	binary.write((const char*)&strProd.price, sizeof(strProd.price));
	if (!binary)
	{
		std::cerr << "Something went wrong when writing to the file\n";
		// file stream error handling
	}


	// Reading
	Product_With_String toRead2;
	binary.seekg(0, std::ios::beg);

	binary.read((char*)&nameLength, sizeof(nameLength));
	char* buffer = new char[nameLength + 1];	// if we write the terminating null in the file, here would be nameLength (without +1)
	binary.read(buffer, nameLength);
	buffer[nameLength] = '\0';
	toRead2.name = buffer;
	delete[] buffer;

	binary.read((char*)&noteLength, sizeof(noteLength));
	buffer = new char[noteLength + 1];	// if we write the terminating null in the file, here would be nameLength (without +1)
	binary.read(buffer, noteLength);
	buffer[noteLength] = '\0';
	toRead2.note = buffer;
	delete[] buffer;

	binary.read((char*)&toRead2.quantity, sizeof(toRead2.quantity));
	binary.read((char*)&toRead2.price, sizeof(toRead2.price));
	if (!binary)
	{
		std::cerr << "Something went wrong when writing to the file\n";
		// file stream error handling
	}

	toRead2.print();

	binary.close();

	return 0;
}
