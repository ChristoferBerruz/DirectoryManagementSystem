#include "BusinessContact.h"
#include "Contact.h"
#include <iostream>

using namespace std;
BusinessContact::BusinessContact(const string& businessName, const string& businessType)
	:Contact(businessName), businessType(businessType)
{

}

void BusinessContact::display() const
{
	Contact::display();
	cout << "Business Type: " << businessType << endl;
}