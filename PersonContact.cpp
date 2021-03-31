#include "PersonContact.h"

#include <iostream>

using namespace std;
PersonContact::PersonContact(const string& fullName, const string& gender) :Contact(fullName), gender(gender)
{

}

void PersonContact::Display() const
{
	Contact::Display();
	cout << "Gender: " << gender << endl;
}