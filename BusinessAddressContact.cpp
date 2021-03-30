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

void BusinessAddressContact::Display() const
{
	BusinessContact::Display();
	cout << "Address: " << address << endl;
}