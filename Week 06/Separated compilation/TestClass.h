// "#pragma once" means that if this file is included more than once in other files of
// the project, it will include it only once
#pragma once


// Normally in header (.h) files we only write the class and all of its members declarations.
// However we define all of them in the source (.cpp) file

class TestClass
{
private:
	int number;
	bool deleted;

public:

	TestClass();

	void setNumber(int number);
	void setDeleted(bool value);
	int getNumber() const;
	int isDeleted() const;
};