#include <iostream>

// STATIC members (data members and member functions)
// When a member of a class is static, it means that in every object of the class and also if there is no objects of this class
// there will be a copy of the same one and only variable/function.
// Once changed (if data member) through the class or one of its objects, the value will be changed for the class and every one
// of the other objects of the class.
// 
// How to access it:
// 1. Through the class - <class name>::<member name or method call>
// 2. Through an object of the class - <object name>.<member name or method call>
//

class Record
{
public:
	size_t size;
	static int id;

	static void increment()
	{
		//this->id;	// ERROR - there is no this pointer for static methods
		//size = 3;	// ERROR - static methods cannot access non-static members
		id++;
	}
};

// Defining a static data member / first initializing of the static data member
int Record::id = 12;


int main()
{
	// Below you will see that every time when a static member is accessed or a static method is called,
	// the effect is applied to the class itself and every one of its objects

	std::cout << "Object calls\n";
	Record object;

	std::cout << object.id << std::endl;	// output 12
	object.id = 13;							// value  13
	std::cout << object.id << std::endl;	// output 13
	object.increment();						// value  14
	object.increment();						// value  15
	std::cout << object.id << std::endl;	// output 15

	Record::id = 3;							// value  3
	std::cout << "Class calls\n";
	std::cout << Record::id << std::endl;	// output 3
	Record::increment();					// value  4
	object.increment();						// value  5
	std::cout << "Object call: " << object.id << std::endl;	// output 5
	std::cout << "Class call: " << Record::id << std::endl;	// output 5

	return 0;
}