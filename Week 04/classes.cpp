#include <iostream>

// Object-oriented programming (OOP)

// The four pillars of OOP (with very short descriptions):
// 1. Encapsulation - hiding data that shouldn't be public; introducing access modifiers; we use it to create some security as well
// 2. Abstraction - we use something knowing what it does, not how it does it; we know only what we should care about and nothing more
// 3. Polymorphism - referring two or more different things by using only one thing (for example something that unites them, a common property for all of them)
// 4. Inheritance - two or more entities having one parent - the have some properties that are the same (they have them from the parent) but also unique properties (only they have them)
// Or again, two or more entities that have common properties but aren't the same, we can refer them polymorphically through their parent but there are different things
// For example: We have Person. It can be inherited by Student and Employee. Every student and every employee have the same properties as a person.
// But they have also unique properties. And not every person is student or employee. (we will discuss it deeper in the Inheritance topic)


// Access modifiers
// public - the public members are reachable all over the program if we refer them using their object/class
// protected - the protected members are reachable only by the inheritor class/object
// private - the private members are reachable only in the current class/object scope

// if it is not explicitly said, all members of a structure have the 'public' access modifier
struct Address
{
public:
	const char* city;
	const char* street;
	int streetNumber;
};

// if it is not explicitly said, all members of a class have the 'private' access modifier
// That is the ONLY difference between structures and classes. In every other case they behave the same.
class Person
{
private:
	int egn;
public:
	const char* name = "Pesho";
	int age;

	Address address;

	void function()
	{
		egn = 5;
	}
};

int main()
{
	char arr[] = "Example";
	Address address{ arr, arr, 45 };	// we can use this constructor only for public members

	Person* pesho = new Person;
	pesho->age = 14;
	pesho->address = address;

	delete pesho;

	return 0;
}