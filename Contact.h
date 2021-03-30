#ifndef CONTACT_H
#define CONTACT_H

#include <string>

using namespace std;
class Contact
{
private:
	string name;
public:
	Contact(const string& name);
	virtual void display() const;
};
#endif // !CONTACT_H

