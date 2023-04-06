// "#include "TestClass.h"" is used so that we have access to the declarations in the TestClass.h file
#include "TestClass.h"

// definition of the constructor;
// initializing the data members, using the initializer list
TestClass::TestClass() : number(-1), deleted(false)
{
    // we can still have code in the body, for example validations, constructing nested classes and so on
}

void TestClass::setNumber(int number)
{
	this->number = number;
}

void TestClass::setDeleted(bool value)
{
	this->deleted = value;
}

int TestClass::getNumber() const
{
	return this->number;
}

int TestClass::isDeleted() const
{
	return this->deleted;
}
