#include "Contact.h"

#include <iostream>

using namespace std;
Contact::Contact(const string& name) :name(name)
{

}

void Contact::Display() const
{
	cout << "Name: " << name << endl;
}