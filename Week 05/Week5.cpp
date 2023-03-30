#include <iostream>

class Address
{
public:
	const char* city;
	const char* street;
	int streetNumber;
};

class Person
{
private:
	int egn;
	const char* name = "Pesho";
	int age;

	Address address;

public:

	// two new concepts - getters and setters, which ensure the correct way of using objects and classes
	// and support the OOP principles encapsulation and abstraction
	// 
	// getters - methods in the class that only return information about the state of the object.
	// They are also called read-only functions, meaning that nobody can modify the object calling them, and are used
	// for receiving information about the state. Getters are always *const functions* (see below)
	// 
	// setters - methods in the class that are used to change the state of an object (by changing one or more of the data-members).
	// They are used to modify the object state by validating every of its changes and processing possible errors.
	//
	// *Const functions* (like getters) are functions used for read-only functions
	// or also functions that do not change the state of the object.
	// They are marked as const with the keyword "const" after the parameter list and before the curly brackets {} for the body

	int getAge() const
	{
		return this->age;
	}

	void setAge(const int age)	// setters are used to validate for possible uncorrect parameters, values etc.
	{
		if (age < 0)	// validating the age - cannot be negative number
		{
			this->age = 0 - age;	// turn the value into its positive (> 0) equivalent
		}
		else
		{
			this->age = age;
		}
	}

	void sayHello() const
	{
		std::cout << "hello";
	}

	// declaring a method without defining it
	void print() const;
};


// another way of definig an already declared method, using the "<classname>::" syntax (in this case Person::)
// "<classname>::" is used to show in which scope is the thing we want to refer after that syntax (in this case we show in which scope is the print() method defined

void Person::print() const
{
	std::cout << name << std::endl;
}

int main()
{
	char arr[] = "Example";
	Address address{ arr, arr, 45 };	// we can use this constructor only for public members

	Person* pesho = new Person;

	pesho->setAge(13);
	pesho->print();
	pesho->sayHello();

	delete pesho;

	return 0;
}