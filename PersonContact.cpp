#include "Contact.h"
#include "PersonContact.h"

#include <iostream>

using namespace std;
PersonContact::PersonContact(const string& fullName, const string& gender) :Contact(fullName), gender(gender)
{

}

void PersonContact::display() const
{
	Contact::display();
	cout << "Gender: " << gender << endl;
}