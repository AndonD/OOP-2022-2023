//#pragma warning(disable:4996)
//
//#include <iostream>
//#include <fstream>
//
//const char* ERROR_MESSAGE = "Couldn't open file correctly\n";
//
////Task - shop
//
//struct Product
//{
//	char* name;
//	size_t quantity;
//	float price;
//
//	void print()
//	{
//		std::cout << name << std::endl;
//		std::cout << quantity << std::endl;
//		std::cout << price << std::endl;
//		std::cout << std::endl;
//	}
//};
//
//void printProducts(Product* products, const size_t& size)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		products[i].print();
//	}
//	std::cout << "------------" << std::endl;
//}
//
//void freeMemory(Product* products, const size_t& size)
//{
//	for (size_t i = 0; i < size; i++)
//	{
//		delete[] products[i].name;
//	}
//	delete[] products;
//}
//
//// function to clear the flags in the file and return the streampos to the beginning
//void rewind(std::fstream& stream)
//{
//	stream.clear();
//	stream.seekg(0, std::ios::beg);
//}
//
//void resize(Product* products, size_t& size, size_t& capacity)
//{
//	size_t newCapacity = capacity * 2;
//	Product* temp = new Product [newCapacity];
//	for (size_t i = 0; i < size; ++i)
//	{
//		temp[i].name = new char[strlen(products[i].name) + 1];
//		
//		strcpy(temp[i].name, products[i].name);
//		temp[i].quantity = products[i].quantity;
//		temp[i].price = products[i].price;
//	}
//
//	freeMemory(products, size);
//
//	products = temp;
//	capacity = newCapacity;
//}
//
//// function to read the data from the file, used for database
//void loadData(Product* products, size_t& size, size_t& capacity, std::fstream& shop)
//{
//	rewind(shop);
//
//	char line[100];
//	while (!shop.eof())
//	{
//		if (size >= capacity)
//		{
//			resize(products, size, capacity);
//		}
//		shop.getline(line, 100);						// reading the whole line, but max 100 characters
//
//		if (strcmp(line, "") == 0)
//			continue;
//
//		products[size].name = new char[strlen(line) + 1];	// allocating memory for the line
//		strcpy(products[size].name, line);					// copying the content from the line to the product's name
//		shop >> products[size].quantity;
//		shop >> products[size].price;
//		++size;												// updating the size value
//
//		shop.ignore();	// skipping the leftover newline character so that we can use getline in the next iteration
//
//		// !!!!!!!!!!
//		// NOTE:
//		// It is not a good practice to read 100 characters with getline!
//		// It is better to read the characters one by one using ifstream.get() and resizing the capacity of the string like in 
//		// the resize() function
//	}
//
//}
//
//// function to read new products from the console and add them to the shop in the file, used for database
//void newStock(Product* products, size_t& size, size_t& capacity, std::fstream& shop)
//{
//	if (!shop.good())
//		shop.clear();
//
//	char line[100];
//	std::cin.getline(line, 100);
//
//	while (strcmp(line, "end"))		// strcmp will return 0 if the two strings have the same content
//	{
//		if (size >= capacity)
//		{
//			resize(products, size, capacity);
//		}
//
//		products[size].name = new char[strlen(line) + 1];
//		strcpy(products[size].name, line);
//		std::cin >> products[size].quantity;
//		std::cin >> products[size].price;
//		std::cin.ignore();
//
//		shop << products[size].name << std::endl;
//		shop << products[size].quantity << std::endl;
//		shop << products[size].price << std::endl;
//		++size;
//
//		std::cin.getline(line, 100);
//	}
//}
//
//
//int main()
//{
//	size_t size = 0;
//	size_t capacity = 16;
//	Product* products = new Product [capacity];
//
//	std::fstream shop("shop with structs.txt", std::ios::in | std::ios::out | std::ios::app);
//	if (!shop.is_open())
//	{
//		std::cerr << ERROR_MESSAGE;
//		return -1;
//	}
//
//	loadData(products, size, capacity, shop);
//	printProducts(products, size);
//
//	newStock(products, size, capacity, shop);
//	printProducts(products, size);
//
//	shop.close();
//
//	freeMemory(products, size);
//
//	return 0;
//}