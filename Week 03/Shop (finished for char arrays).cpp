#pragma warning(disable:4996)

#include <iostream>
#include <fstream>

const char* ERROR_MESSAGE = "Couldn't open file correctly\n";

//Task - shop

void printProducts(char** products, const size_t& size)
{
	for (size_t i = 0; i < size; i++)
	{
		std::cout << products[i] << std::endl;
	}
	std::cout << std::endl;
}

void freeMemory(char** products, const size_t& size)
{
	for (size_t i = 0; i < size; i++)
	{
		delete[] products[i];
	}
	delete[] products;
}

// function to clear the flags in the file and return the streampos to the beginning
void rewind(std::fstream& stream)
{
	stream.clear();
	stream.seekg(0, std::ios::beg);
}

void resize(char** str, size_t& size, size_t& capacity)
{
	size_t newCapacity = capacity * 2;
	char** temp = new char* [newCapacity];
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = new char[strlen(str[i]) + 1];
		strcpy(temp[i], str[i]);
	}

	freeMemory(str, size);

	str = temp;
	capacity = newCapacity;
}

// function to read the data from the file, used for database
void loadData(char** products, size_t& size, size_t& capacity, std::fstream& shop)
{
	rewind(shop);

	char line[100];
	while (!shop.eof())
	{
		if (size >= capacity)
		{
			resize(products, size, capacity);
		}
		shop.getline(line, 100);						// reading the whole line, but max 100 characters

		if (strcmp(line, "") == 0)	// skipping blank lines
			continue;

		products[size] = new char[strlen(line) + 1];	// allocating memory for the line
		strcpy(products[size], line);					// copying the content from the line to the products
		++size;											// updating the size value

		// !!!!!!!!!!
		// NOTE:
		// It is not a good practice to read 100 characters with getline!
		// It is better to read the characters one by one using ifstream.get() and resizing the capacity of the string like in 
		// the resize() function
	}

}

// function to read new products from the console and add them to the shop in the file, used for database
void newStock(char** products, size_t& size, size_t& capacity, std::fstream& shop)
{
	if (!shop.good())
		shop.clear();

	char line[100];
	std::cin.getline(line, 100);

	while (strcmp(line, "end"))		// strcmp will return 0 if the two strings have the same content
	{
		if (size >= capacity)
		{
			resize(products, size, capacity);
		}
		products[size] = new char[strlen(line) + 1];
		strcpy(products[size], line);

		shop << products[size] << '\n';
		++size;

		std::cin.getline(line, 100);
	}
}


int main()
{
	size_t size = 0;
	size_t capacity = 16;
	char** products = new char* [capacity];

	std::fstream shop("shop.txt", std::ios::in | std::ios::out | std::ios::app);
	if (!shop.is_open())
	{
		std::cerr << ERROR_MESSAGE;
		return -1;
	}

	loadData(products, size, capacity, shop);
	printProducts(products, size);

	newStock(products, size, capacity, shop);
	printProducts(products, size);

	shop.close();

	freeMemory(products, size);

	return 0;
}