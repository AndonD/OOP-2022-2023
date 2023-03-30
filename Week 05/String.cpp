#pragma warning(disable:4996)

#include <iostream>
#include <cstring>

//-------------------------------------------------------------------------------------------------------
// 
// Every object of a class in C++ has a lifecycle/lifetime. That means that the object does not exist
// forever and is created and destroyed. Here are the stages of a lifecycle:
// 1. Creating - every object is first created. Normally we store objects in variables with a
//		name. This means that we can refer the object through its name (identifier) from now on
// 2. Living - this is the phase, where an object exists and can be referred, read, mutated
//		an so on.
// 3. Destroying - every object, stored in a variable, has a scope of accessibility. Once this scope ends
//		and there is no referrence to the object, it is destroyed.
// 
// Objects are created via constructors. Constructors are methods which have no return type and their name
// is exactli the same as the name of the class. They cannot be explicitly called.
// 
// There are four types of constructors:
// 1. Default constructor - has no parameters and sets the default state for a class when it is created.
//		If we do not define explicitly a default constructor, C++ provides one for us, but does not do
//		any validations or something like this.
// 2. Constructor with parameters - there can be more than one constructor with parameters. Their idea is
//		that we can pass the object some parameters to be used for the initialization of the object.
// 3. Copy constructor - we will discuss it the next week
// 4. Move constructor - we will discuss it the next week
// 
//-------------------------------------------------------------------------------------------------------

class String
{
private:
	char* str;
	size_t capacity;
	size_t size;

public:

	// default constructor
	String()
	{
		size = 0;
		capacity = 8;
		str = new char[8];
		str[size] = '\0';
	}

	// constructor with parameters
	String(const char* content)
	{
		size = strlen(content);
		capacity = 8;
		while (capacity <= size)
		{
			capacity *= 2;
		}

		str = new char[capacity];
		strcpy(str, content);
	}

	// destructor
	~String()
	{
		delete[] str;
	}

	size_t length() const
	{
		return this->size;	// return strlen(this->str);
	}

	char* c_str() const
	{
		return this->str;
	}

	void print() const
	{
		std::cout << str << std::endl;
	}
};

// TODO for next week
String concat(String first, String second)
{
	/*char* temp = new char[first.length() + second.length() + 1];
	strcpy(temp, first.c_str());
	strcat(temp, second.c_str());

	String result(temp);
	
	delete[] temp;
	return result;*/
}


int main()
{
	String str1("test ");
	str1.print();
	String str2("another str");
	str2.print();
	return 0;
}