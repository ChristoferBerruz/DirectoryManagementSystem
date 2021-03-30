#include "BusinessAddressContact.h"
#include "BusinessPhoneContact.h"
#include "BusinessWebContact.h"
#include "PersonEmailContact.h"
#include "PersonAddressContact.h"
#include "PersonPhoneContact.h"
#include "Contact.h"

#include <iostream>
using namespace std;
int main()
{
	Contact* contacts[6];
	contacts[0] = new BusinessAddressContact("University of Bridgeport", "University", "126 Park Ave, Bridgeport, CT 06604");
	contacts[1] = new BusinessPhoneContact("Fairfield University", "University", "(800) 392-3582");
	contacts[2] = new BusinessWebContact("Goodwin University", "University", "admissions@bridgeport.edu", "www.bridgeport.edu");
	contacts[3] = new PersonAddressContact("Jhon Smith", "Male", "1491 Scelerisque Av. Fort Wayne, IN ,53759");
	contacts[4] = new PersonEmailContact("Susana", "Female", "susana@gmail.com");
	contacts[5] = new PersonPhoneContact("Vladimir", "Male", "1-176-320-8624");
	for (int i = 0; i < 6; i++) {
		contacts[i]->display();
		cout << "--------------------------" << endl;
	}
	return 0;
}