#include <iostream>
#include <exception>

// https://cplusplus.com/doc/tutorial/exceptions/

int main()
{
	try
	{
		int age = 15;
		if (age >= 18)
		{
			std::cout << "Access granted - you are old enough.";
		}
		else if (0 <= age && age < 18)
		{
			throw (age);
		}
		else
		{
			throw ("Age cannot be less than zero");
		}
	}
	catch (int myNum)
	{
		std::cout << "Access denied - You must be at least 18 years old.\n";
		std::cout << "Age is: " << myNum;
	}
	catch (const char* message)
	{
		std::cout << message << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown error" << std::endl;
	}


	try
	{
		try
		{
			throw 20;
		}
		catch (int num)
		{
			std::cout << "Handle Partially ";
			throw; // Re-throwing an exception
		}
	}
	catch (int num)
	{
		std::cout << "Handle remaining ";
	}

	try
	{
		throw std::exception("Some exception");
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}