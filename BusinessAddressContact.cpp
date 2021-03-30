#include "BusinessAddressContact.h"
#include <iostream>

using namespace std;
BusinessAddressContact::BusinessAddressContact(
	const string& businessName,
	const string& businessType,
	const string& address
) :BusinessContact(businessName, businessType), address(address)
{

}

void BusinessAddressContact::display() const
{
	BusinessContact::display();
	cout << "Address: " << address << endl;
}