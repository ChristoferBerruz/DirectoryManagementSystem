#include "Contact.h"

#include <iostream>

using namespace std;
Contact::Contact(const string& name) :name(name)
{

}

void Contact::display() const
{
	cout << "Name: " << name << endl;
}