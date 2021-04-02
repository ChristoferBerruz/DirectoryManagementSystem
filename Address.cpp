#include "Address.h"
using namespace std;

Address::Address(const string& streetAddress, const string& city, const string& state, const string& zipcode)
	:streetAddress(streetAddress), city(city), state(state), zipcode(zipcode)
{

}


string Address::GetStreet() const
{
	return streetAddress;
}

string Address::GetCity() const
{
	return city;
}

string Address::GetState() const
{
	return state;
}


string Address::GetZipcode() const
{
	return zipcode;
}

void Address::SetStreet(const string& street) 
{
	streetAddress = street;
}

void Address::SetCity(const string& city)
{
	(*this).city = city;
}

void Address::SetState(const string& state)
{
	(*this).state = state;
}

void Address::SetZipcode(const string& zipcode)
{
	(*this).zipcode = zipcode;
}

ostream& operator<<(ostream& os, Address address)
{
	os << address.streetAddress << ", ";
	os << address.city << ", ";
	os << address.state << ", ";
	os << address.zipcode << "\n";

	return os;
}