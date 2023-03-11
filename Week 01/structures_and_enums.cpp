#include <iostream>

// enums

// enum - enumeration, every value could be casted into integer; you can specify the numeric values, by default starts with 0, 1, etc.
enum statusOfProgram
{
	building = 4,
	compiling = -2,
	running,	// running = (compiling + 1) = -1
	ended,		// ended = (running + 1) = 0
	undefined	// we should always have a value for cases when there is an error or somehow the other values don't work for us
};

// enum class - the same as normal enum, except that values cannot be casted into integer;
// we cannot use the numeric value of "android", we use it only as the enum value "android" itself
enum class operationSystem //enum class == enum struct
{
	android,	// 0
	macOS,		// 1
	windows,	// 2
	linux		// 3
};


// structures

struct Address
{
	const char city[16];
	const char street[16];
	int streetNumber;


	// A structure can have functions inside itself, they are called methods.
	// They work exactly the same as normal functions, but you can access them only through an object of the structure.
	// They also have access to every member or method declared in the same struct.

	void print()
	{
		std::cout << "City: " << city << std::endl;
		std::cout << "Street: " << street << std::endl;
		std::cout << "Street number: " << streetNumber << std::endl;
	}
};

// a structure can have members whose type is another structure, like Address in the example
struct Person
{
	const char name[16];
	int age;
	int egn;

	Address address;

	void print()
	{
		std::cout << "Name: " << name << std::endl;
		std::cout << "Age: " << age << std::endl;
		std::cout << "EGN: " << egn << std::endl;
		std::cout << "Address:\n";
		address.print();
	}
};

// We can access members or methods of an object of a structure by typing its name followed by "."
// object name is "somePerson", therefore we access with "somePerson." + the member/method name as showed below
void print(const Person& somePerson)
{
	std::cout << "Name: " << somePerson.name << std::endl;
	std::cout << "Age: " << somePerson.age << std::endl;
	std::cout << "EGN: " << somePerson.egn << std::endl;
	std::cout << "Address:\n";
	
	Address address = somePerson.address;	// making a copy of the person's address, later we'll discuss why we need a copy
	address.print();

}

int main()
{
	// this is the so called canonical constructor (каноничен конструктор);
	// when using it, we must give parameter values in the same order as they are in the structure declaration
	// Note that the last member ot Person is a structure of type Address, but we can use the same constructor for it in the parameters list
	
	Person petar{ "Petar", 20, 237893, {"Kaspichan", "Petko Todorov", 12} };
	// equivalent as:
	Person pesho{ "Pesho", 20, 237892, "Kaspichan", "Petko Todorov", 12 };	// only in this case we can miss the curly braces of the structure which is parameter (Address in this case)



	// these are two different functions (one is a method of Person, the other is the global function print(const Person& somePerson)
	
	print(pesho);
	pesho.print();


	// Remember the structure padding rules

	std::cout << sizeof(Address) << std::endl;
	std::cout << sizeof(Person) << std::endl;



	//enums demo
	
	statusOfProgram status = running;	// running == statusOfProgram::running

	operationSystem errorSystem = android;							// throws an error
	operationSystem system = operationSystem::android;				// works fine

	std::cout << 1 + status;	// works fine
	std::cout << 1 + system;	// throws an error, because system cannot be converted/casted to int

	std::cout << 1 + (status == statusOfProgram::running ? 2 : -1);	// this is the valid way to do the same as above with enum class
	
	return 0;
}