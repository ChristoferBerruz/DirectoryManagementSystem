#include "BusinessContact.h"
#include "Contact.h"
#include <iostream>

using namespace std;
BusinessContact::BusinessContact(const string& name, const string& category)
	:Contact(name), category(category)
{

}

void BusinessContact::display() const
{
	Contact::display();
	cout << "Category: " << category << endl;
}