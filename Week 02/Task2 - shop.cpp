#include <iostream>
#include <fstream>

int main()
{
	//shop.inf
	std::fstream shop("shop.informatika", std::ios::out);
	char products[5][10];

	if (!shop.is_open())
	{
		std::cerr << "ERROR opening file!\n";
		return -1;
	}

	for (size_t i = 0; i < 5; i++)
	{
		std::cin >> products[i];
		shop << products[i] << std::endl;
	}

	shop.close();


	shop.open("shop.informatika", std::ios::in);

	if (!shop.is_open())
	{
		std::cerr << "ERROR opening file!\n";
		return -1;
	}

	for (size_t i = 0; i < 5; i++)
	{
		size_t index = 0;
		while (!shop.eof() && index < 5)
		{
			shop >> products[index];
			std::cout << products[index] << std::endl;
			++index;
		}
	}

	shop.close();

	return 0;
}