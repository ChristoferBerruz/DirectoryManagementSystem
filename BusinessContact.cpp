#include "BusinessContact.h"
#include <iostream>

using namespace std;
BusinessContact::BusinessContact(const string& name, const string& category)
	:Contact(name), category(category)
{

}

void BusinessContact::Display() const
{
	Contact::Display();
	cout << "Category: " << category << endl;
}