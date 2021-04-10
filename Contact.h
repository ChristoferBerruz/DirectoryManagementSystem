#ifndef CONTACT_H
#define CONTACT_H

#include <string>

using namespace std;
class Contact
{
private:
	string name;
public:
	string GetName() { return name; }
	Contact(const string& name);
	virtual void Display() const;
};
#endif // !CONTACT_H

