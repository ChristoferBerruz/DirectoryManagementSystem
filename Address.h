#ifndef ADDRESS_H
#define ADDRESS_H
#include <string>
#include <iostream>
using namespace std;
class Address
{
private:
	string streetAddress;
	string city;
	string state;
	string zipcode;
public:
	Address(const string& streetAddress, const string& city, const string& state, const string& zipcode);
	string GetStreet() const;
	string GetCity() const;
	string GetState() const;
	string GetZipcode() const;
	void SetStreet(const string& street);
	void SetCity(const string& city);
	void SetState(const string& state);
	void SetZipcode(const string& zipcode);
	friend ostream& operator<<(ostream& os, Address address);
};
#endif // !ADDRESS_H
